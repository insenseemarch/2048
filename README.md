# 🎮 Game 2048  

---

## Thông tin cơ bản về trò chơi 2048

> ⚠️ **Lưu ý:** Do code có sử dụng một số hàm khống chế kích thước và con trỏ chuột, vui lòng chạy chương trình bằng **cmd (Windows Console Host)** thay vì Windows Terminal.  
> 👉 Cách thay đổi trên Windows 11: Vào **Terminal Settings** → mục **Terminal** → đổi thành **Windows Console Host**.

### Màn hình cửa sổ bắt đầu
(người chơi chọn các chức năng TRƯỚC khi nhập tên ở New Game)

#### a. New Game
- Người chơi nhập **ID** (dưới 20 ký tự).
- ID phải **không trùng** trong Top-20 và Resume-List.
- ID hợp lệ chỉ chứa **chữ và số** (không cho phép ký tự đặc biệt).
- Lưu ý: khi nhập tên có dùng `cin.ignore(..., '\n')` → một số trường hợp cần **nhấn Enter 2 lần**.

#### b. Game Settings
- Điều chỉnh kích thước bàn cờ: mặc định **4x4**, tối đa **10x10**.
- Bật/tắt chức năng **Undo** hoặc **Undo & Redo** (mặc định tắt).
- Chọn ngôn ngữ: **English** (mặc định) hoặc **Tiếng Việt**.
- Có thể quay về menu.

#### c. Top-20 List
- Hiển thị danh sách 20 người chơi có thành tích cao nhất.  
- Tiêu chí xếp hạng:
  1. Điểm càng cao → hạng càng cao.
  2. Nếu bằng điểm → thời gian càng ngắn → hạng càng cao.
  3. Nếu trùng tên (Resume) → lần chơi có thời gian dài hơn → giữ hạng, xoá bản cũ.
- Trường hợp người chơi top 1 chọn Undo → điểm cao nhất vẫn được giữ lại trong Top-20.

#### d. Resume
- Cho phép lưu tối đa **5 tài khoản Resume** (`player-i-.bin` với i từ 1 đến 5).
- Nếu đã đủ 5 slot, từ tài khoản thứ 6 trở đi → có thể chọn ghi đè 1 trong 5 slot cũ.
- Hỗ trợ lưu Undo/Redo nếu bật chức năng.

> 🕹️ Tại màn hình bắt đầu, điều khiển bằng phím **lên/xuống/trái/phải** và các phím **Y/N** khi có yêu cầu.

---

### Màn hình chính trong trò chơi
- **[w]**: di chuyển lên  
- **[d]**: di chuyển sang phải  
- **[a]**: di chuyển sang trái  
- **[s]**: di chuyển xuống  
- **[x]**: thoát màn hình  
- **[u]**: Undo (nếu bật)  
- **[r]**: Redo (nếu bật)

#### Các trường hợp:
- **Thoát [x]**: thông tin tự động lưu, người chơi chọn có muốn Resume không.  
- **Thua cuộc**: chỉ lưu nếu vào Top-20, không cho Resume. Có thể Undo (nếu bật) hoặc New Game.  
- **Thắng cuộc**: thông tin tự động lưu, người chơi có thể chọn tiếp tục hoặc Resume để lưu file.

---

### Một số chức năng mở rộng
- 🔒 **Mã hóa file bằng XOR** khi Resume để bảo vệ dữ liệu.  
- 💾 Hỗ trợ Resume cho **5 tài khoản**.  
- 🌐 Có thể chuyển đổi ngôn ngữ **Anh ↔ Việt**.  
