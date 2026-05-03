import cv2
import numpy as np

# ========== Trackbar Callback ==========
def nothing(x):
    pass

# ========== เปิดกล้อง ==========
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

if not cap.isOpened():
    print("❌ เปิดกล้องไม่ได้")
    exit()

# ========== สร้างหน้าต่าง Trackbar ==========
cv2.namedWindow("HSV Tuner")

# Lower HSV
cv2.createTrackbar("H Min", "HSV Tuner", 0,   179, nothing)
cv2.createTrackbar("S Min", "HSV Tuner", 0,   255, nothing)
cv2.createTrackbar("V Min", "HSV Tuner", 0,   255, nothing)

# Upper HSV
cv2.createTrackbar("H Max", "HSV Tuner", 179, 179, nothing)
cv2.createTrackbar("S Max", "HSV Tuner", 255, 255, nothing)
cv2.createTrackbar("V Max", "HSV Tuner", 255, 255, nothing)

print("✅ เปิด HSV Tuner แล้ว กด Q เพื่อออก")
print("ปรับ Trackbar เพื่อหาค่า HSV ที่ต้องการ")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # อ่านค่าจาก Trackbar
    h_min = cv2.getTrackbarPos("H Min", "HSV Tuner")
    s_min = cv2.getTrackbarPos("S Min", "HSV Tuner")
    v_min = cv2.getTrackbarPos("V Min", "HSV Tuner")
    h_max = cv2.getTrackbarPos("H Max", "HSV Tuner")
    s_max = cv2.getTrackbarPos("S Max", "HSV Tuner")
    v_max = cv2.getTrackbarPos("V Max", "HSV Tuner")

    # แปลงเป็น HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # สร้าง Mask
    lower = np.array([h_min, s_min, v_min])
    upper = np.array([h_max, s_max, v_max])
    mask = cv2.inRange(hsv, lower, upper)

    # แสดงผล
    result = cv2.bitwise_and(frame, frame, mask=mask)

    # แสดงค่า HSV บนจอ
    cv2.putText(frame,
                f"Lower: H={h_min} S={s_min} V={v_min}",
                (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
    cv2.putText(frame,
                f"Upper: H={h_max} S={s_max} V={v_max}",
                (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

    # แสดงหน้าต่าง
    cv2.imshow("HSV Tuner",  frame)   # ภาพปกติ
    cv2.imshow("Mask",       mask)    # Mask ขาวดำ
    cv2.imshow("Result",     result)  # ภาพที่กรองสีแล้ว

    # กด S เพื่อบันทึกค่า
    key = cv2.waitKey(1) & 0xFF
    if key == ord('s'):
        print("\n========== ค่า HSV ที่ได้ ==========")
        print(f"lower = np.array([{h_min}, {s_min}, {v_min}])")
        print(f"upper = np.array([{h_max}, {s_max}, {v_max}])")
        print("=====================================\n")

    elif key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()