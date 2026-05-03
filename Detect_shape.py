import cv2
import numpy as np

cap = cv2.VideoCapture(0)  # แก้ตรงนี้
cap.set(3, 640)
cap.set(4, 480)

if not cap.isOpened():
    print("ERROR เปิดกล้องไม่ได้ ลองเปลี่ยน index เป็น 1 หรือ 2")
    exit()

print("OK เปิดกล้องสำเร็จ กด ESC เพื่อออก")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    color_ranges = {
        "Red":   [(0, 167, 191),  (179, 255, 255)],
        "Green": [(66,  80,  80),  (80,  255, 255)],
        "Blue":  [(90,  50,  70),  (128, 255, 255)]
    }

    for color_name, (lower, upper) in color_ranges.items():
        lower = np.array(lower)
        upper = np.array(upper)
        mask  = cv2.inRange(hsv, lower, upper)
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for cnt in contours:
            area = cv2.contourArea(cnt)
            if area < 1000:
                continue

            approx = cv2.approxPolyDP(cnt, 0.04 * cv2.arcLength(cnt, True), True)
            sides  = len(approx)
            shape  = ""

            if sides == 4:
                x, y, w, h = cv2.boundingRect(approx)
                ratio = float(w) / h
                if 0.9 <= ratio <= 1.1:
                    shape = "Square"
            elif sides == 6:
                shape = "Hexagon"

            if shape != "":
                cv2.drawContours(frame, [approx], -1, (0, 255, 0), 3)
                cv2.putText(frame, f"{color_name} {shape}",
                            (approx[0][0][0], approx[0][0][1]),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.6, (255, 255, 255), 2)
                print(f"เจอ: {color_name} {shape} | Area: {int(area)}")

    cv2.imshow("Camera", frame)

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()