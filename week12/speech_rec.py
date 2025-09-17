import re
import serial
import speech_recognition as sr

# ================== Serial Setup ==================
# ⚠️ เปลี่ยน COM5 ให้ตรงกับพอร์ต ESP32 ของคุณ
ser = serial.Serial("COM3", 9600, timeout=0.6)

# แปลงเลขไทยเป็นเลขอารบิก เช่น ๙๐ -> 90
THAI_DIGITS = str.maketrans("๐๑๒๓๔๕๖๗๘๙", "0123456789")

# “โหมด 5 มุม” — เซ็ตมุมมาตรฐาน
ALLOWED_ANGLES = [0, 45, 90, 135, 180]

def normalize_text(s: str) -> str:
    """ตัดช่องว่างซ้ำ ๆ และแปลงเลขไทยเป็นอารบิก"""
    s = re.sub(r"\s+", " ", s.strip())
    return s.translate(THAI_DIGITS)

def parse_angle(cmd: str):
    """ดึงตัวเลขมุมจากคำสั่ง ทั้งไทยและอังกฤษ"""
    # อังกฤษ
    m = re.search(r"\b(?:rotate|turn)\s*(?:to\s*)?(\d{1,3})\s*(?:degree|degrees)?\b", cmd, re.I)
    if not m:
        # ไทย
        m = re.search(r"(?:สั่งงาน\s*)?หมุน(?:มอเตอร์)?(?:ไปที่|ที่)?\s*(\d{1,3})", cmd)
    if not m:
        return None

    angle = int(m.group(1))
    return max(0, min(180, angle))  # จำกัดช่วงเซอร์โว 0..180

r = sr.Recognizer()
with sr.Microphone() as mic:
    r.adjust_for_ambient_noise(mic, duration=0.6)
    print("พูดขึ้นต้นว่า 'สวัสดี' แล้วตามด้วยคำสั่ง เช่น 'สั่งงาน หมุน 90' หรือ 'Rotate 90 degrees'")

    while True:
        try:
            audio = r.listen(mic, timeout=6, phrase_time_limit=10)
            text = r.recognize_google(audio, language="th-TH")
            print("ได้ยิน:", text)

            tnorm = normalize_text(text)

            if tnorm.startswith("สวัสดี"):
                cmd = tnorm.replace("สวัสดี", "", 1).strip()

                # ----------- โหมด “5 มุม” -----------
                if re.search(r"\b5\s*มุม\b", cmd) or re.search(r"\bfive\s*angles\b", cmd, re.I):
                    for a in ALLOWED_ANGLES:
                        msg = f"ROTATE:{a}\n"
                        ser.write(msg.encode())
                        print("ส่ง:", msg.strip())
                    continue

                # ----------- โหมดปกติ -----------
                angle = parse_angle(cmd)
                if angle is not None:
                    nearest = min(ALLOWED_ANGLES, key=lambda a: abs(a - angle))
                    msg = f"ROTATE:{nearest}\n"
                    ser.write(msg.encode())
                    print("ส่ง:", msg.strip())
                else:
                    print("ยังไม่เข้าใจคำสั่งหมุน ลองพูดว่า 'สั่งงาน หมุน 90' หรือ 'Rotate 90 degrees'")
            else:
                print("เริ่มด้วย 'สวัสดี' ก่อนนะครับ 😉")

        except sr.WaitTimeoutError:
            print("ไม่มีเสียงพูดเข้ามาเลยครับ")
        except sr.UnknownValueError:
            print("ฟังไม่ชัดครับ ลองใหม่อีกครั้ง…")
        except Exception as e:
            print("Error:", e)