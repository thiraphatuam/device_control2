
      if(arduino):
        arduino.write((command + '\n').encode())
      else: