# Music Player State Pattern

## 1. Mô tả dự án
Thiết kế phần mềm trình phát nhạc đơn giản sử dụng State Pattern. Trình phát nhạc có các trạng thái: Đang dừng (Stopped), Đang phát (Playing), Đang tạm dừng (Paused). Hành vi của các nút điều khiển (Play, Pause, Stop) thay đổi tùy theo trạng thái hiện tại. Mục tiêu là giúp MusicPlayer thay đổi linh hoạt hành vi khi trạng thái thay đổi, dễ dàng mở rộng thêm trạng thái mới mà không ảnh hưởng đến mã nguồn hiện tại.

## 2. Cấu trúc source code
```
03-state-machince/
├── main.c                
├── Makefile              
├── inc/                 
│   ├── music-player.h        
│   ├── player-state.h         
│   ├── stopped-state.h        
│   ├── playing-state.h      
│   ├── paused-state.h        
│   └── ...                  
├── src/                
│   ├── music-player.c       
│   ├── stopped-state.c        
│   ├── playing-state.c        
│   ├── paused-state.c         
│   └── ...                  
```

## 3. Các API, struct, element chính
- **MusicPlayer (Context):**
  - Quản lý trạng thái hiện tại, cung cấp các hàm clickPlayButton(), clickPauseButton(), clickStopButton().
  - Hàm changeState() để chuyển đổi trạng thái.
- **PlayerState (Interface):**
  - Định nghĩa các hàm: pressPlay(), pressPause(), pressStop().
  - Có thể có setContext() để liên kết với MusicPlayer.
- **StoppedState, PlayingState, PausedState (ConcreteState):**
  - Triển khai PlayerState, định nghĩa hành vi cụ thể cho từng trạng thái.
  - Có thể gọi changeState() để chuyển trạng thái cho MusicPlayer.

## 4. How to build & run
```bash
# Build project
make

# Chạy chương trình
./music-player
```

## 5. Kết quả mẫu

```bash
[TEST] Current state: Stopped
Music is already stopped.

[TEST] Press Play -> Transition to Buffering
Starting music...

[TEST] Buffering complete -> Playing
Buffering success -> Playing

[TEST] Press Pause -> Transition to Paused
Pausing music...

[TEST] Resume from Paused -> Back to Playing
Resuming music...

[TEST] Press Stop -> Back to Stopped
Stopping music...

[TEST] Press Play -> Buffering -> Error occurs
Starting music...
Buffering fail -> next to error state
Error...

[TEST] In Error state: Try pressing Play
Can not play: currently Error

[TEST] In Error state: Try pressing Pause
Can not pause: currently Error

[TEST] In Error state: Press Stop to return to Stopped
Stopping from error state...
```

## 6. Mở rộng
- Dễ dàng thêm trạng thái mới như BufferingState, ErrorState chỉ bằng cách thêm file .h/.c tương ứng và cập nhật Makefile.
- Quản lý code rõ ràng, dễ bảo trì, mở rộng.
