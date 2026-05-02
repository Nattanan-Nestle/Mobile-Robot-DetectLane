import serial
import time

# เปิด Serial
ser = serial.Serial(
    port='/dev/ttyUSB0',  # เปลี่ยนถ้าเป็น ttyACM0
    baudrate=115200,
    timeout=2
)

time.sleep(2)  # รอ ESP32 บูตก่อน

# อ่านข้อความตอนเริ่มต้น
while ser.in_waiting:
    print("ESP32:", ser.readline().decode().strip())

# ฟังก์ชันส่งคำสั่ง
def send_cmd(cmd, delay=2):
    print(f"ส่งคำสั่ง: {cmd}")
    ser.write(f"{cmd}\n".encode())
    time.sleep(0.3)
    while ser.in_waiting:
        response = ser.readline().decode().strip()
        print(f"ESP32 ตอบ: {response}")
    time.sleep(delay)

# ทดสอบ
send_cmd("forward",  delay=2)
send_cmd("stop",     delay=1)
send_cmd("backward", delay=2)
send_cmd("stop",     delay=1)
send_cmd("left",     delay=1)
send_cmd("stop",     delay=1)
send_cmd("right",    delay=1)
send_cmd("stop",     delay=1)

ser.close()
print("เสร็จแล้ว ✅")