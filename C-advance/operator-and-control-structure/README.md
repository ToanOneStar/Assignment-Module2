# Addressable RGB LED Strip Driver (WS2812B/NeoPixel)

## 1. Mô tả dự án
Phát triển driver phần mềm cấp cao để điều khiển dải đèn LED RGB địa chỉ hóa (như WS2812B/NeoPixel). Driver cung cấp các API để khởi tạo, thiết lập màu từng pixel, tô màu toàn dải, tắt dải, và truy xuất buffer dữ liệu màu sẵn sàng gửi đi. Dữ liệu màu cho mỗi LED được đóng gói thành 24-bit (G-R-B) trong một biến uint32_t.

## 2. Cấu trúc source code
```
operator-and-control-structure/
├── led_driver.h       
├── led_driver.c        
├── main.c             
├── Makefile           
```

## 3. Các API, struct, element chính
- **int led_init(size_t num_pixels);**
  - Khởi tạo buffer cho dải LED với số pixel chỉ định. Trả về 0 nếu thành công, -1 nếu lỗi.
- **void led_shutdown();**
  - Giải phóng bộ nhớ đã cấp phát cho buffer.
- **void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);**
  - Thiết lập màu cho pixel tại vị trí index (theo định dạng G-R-B).
- **void led_fill(uint8_t r, uint8_t g, uint8_t b);**
  - Tô toàn bộ dải LED bằng một màu.
- **void led_clear();**
  - Tắt toàn bộ dải LED (màu đen).
- **const uint32_t* led_get_buffer();**
  - Lấy con trỏ chỉ đọc tới buffer dữ liệu màu.
- **size_t led_get_pixel_count();**
  - Lấy số lượng pixel của dải LED.

## 4. How to build & run
```bash
# Build project
make

# Run
./led-driver
```

## 5. Kết quả kiểm thử mẫu
```
=== LED Driver Test Case ===

1. Initializing LED strip with 10 pixels...
[PASS] LED initialization

2. Checking if buffer is initialized to 0...
[PASS] Buffer initialized to 0

3. Setting pixel colors...

4. Verifying pixel colors...
Pixel 0 (Red): Value = 0x0000FF00
[PASS] Pixel 0 is Red
Pixel 9 (Blue): Value = 0x000000FF
[PASS] Pixel 9 is Blue
Pixel 4 (White): Value = 0x00FFFFFF
[PASS] Pixel 4 is White

5. Filling entire strip with Green...

6. Verifying all pixels are Green...
[PASS] All pixels are Green

10. Cleaning up...
[PASS] Cleanup successful

=== Test Complete ===
```

## 6. Giải thích giải pháp
- Dữ liệu màu được đóng gói 24-bit (G-R-B) trong uint32_t, thao tác bit đảm bảo đúng định dạng.
- Các hàm kiểm tra biên an toàn, tránh ghi ngoài vùng nhớ.
- Dễ dàng mở rộng, tích hợp với phần cứng thực tế hoặc mô phỏng kiểm thử.
