# Ứng dụng quản lý chi tiêu cá nhân

## 1. Giới thiệu

Đây là chương trình quản lý chi tiêu cá nhân được viết bằng ngôn ngữ C.  
Chương trình cho phép người dùng ghi lại các khoản thu, khoản chi phân loại theo danh mục, thiết lập ngân sách theo từng tháng và xem báo cáo thống kê chi tiêu.

Dữ liệu của chương trình được lưu vào file csv để có thể đọc lại ở những lần chạy sau.
Khi chương trình khởi động, dữ liệu sẽ được đọc từ các file này.  
Khi người dùng thêm, sửa hoặc xóa dữ liệu, chương trình sẽ cập nhật lại file tương ứng.

## 2. Chức năng chính

Chương trình gồm các chức năng chính sau:

- Đọc dữ liệu từ file và ghi dữ liệu ra file.
- Quản lý giao dịch thu/chi.
- Quản lý ngân sách theo danh mục, tháng và năm.
- Cảnh báo khi chi tiêu vượt quá hạn mức ngân sách.
- Báo cáo thống kê thu, chi theo danh mục.


## 3. Cấu trúc thư mục
```
expense_manager/
│
├── README.md                 # File hướng dẫn sử dụng project
├── .gitignore                # File khai báo các file/thư mục không đưa lên Git
├── .vscode/                  # Cấu hình riêng cho Visual Studio Code
│   └── tasks.json            # Task build/run project trong VS Code
│
├── include/                  # Thư mục chứa các file header (.h)
│   ├── models.h              # Khai báo struct và các biến dùng chung
│   ├── utils.h               # Khai báo các hàm tiện ích
│   ├── transaction.h         # Khai báo các hàm quản lý giao dịch
│   ├── budget.h              # Khai báo các hàm quản lý ngân sách
│   ├── report.h              # Khai báo các hàm báo cáo thống kê
│   └── file_io.h             # Khai báo các hàm đọc/ghi file csv
│
└── src/                      # Thư mục chứa các file mã nguồn (.c)
    ├── main.c                # Hàm main, menu chính và điều phối chương trình
    ├── utils.c               # Cài đặt các hàm tiện ích
    ├── transaction.c         # Cài đặt chức năng thêm, xem, sửa, xóa giao dịch
    ├── budget.c              # Cài đặt chức năng quản lý ngân sách
    ├── report.c              # Cài đặt chức năng báo cáo thống kê
    └── file_io.c             # Cài đặt chức năng đọc/ghi dữ liệu từ file csv
```
## 4. Yêu cầu hệ thống

| Thành phần | Yêu cầu |
|---|---|
| Hệ điều hành | Windows 10/11, Linux hoặc macOS |
| Trình biên dịch | GCC hoặc Clang. Trên Windows có thể dùng MinGW-w64 |
| Môi trường phát triển | Visual Studio Code, CLion, Code::Blocks hoặc bất kỳ IDE/editor nào hỗ trợ C |
| Công cụ build | biên dịch trực tiếp bằng `gcc` |
| Chuẩn ngôn ngữ | C11 |
| Thư viện sử dụng | Chỉ sử dụng thư viện chuẩn của C, không dùng thư viện ngoài |

Chương trình được biên dịch bằng lệnh `gcc` với chuẩn `C11` và sử dụng các file nguồn trong thư mục `src/`, file header trong thư mục `include/`.
## 5. Cách biên dịch và chạy chương trình

Sau khi đã clone về máy, thực hiện các lệnh dưới đây trên terminal tại thư mục gốc của project.

Thư mục gốc là thư mục chứa các thư mục `src`, `include` và file `README.md`.
### Cách 1: Biên dịch trực tiếp bằng GCC
### macOS/Linux

Biên dịch chương trình:

```bash
gcc -std=c11 -Wall -Wextra -pedantic src/main.c src/utils.c src/transaction.c src/budget.c src/report.c src/file_io.c -Iinclude -o expense_manager
```

Chạy chương trình:

```bash
./expense_manager
```

### Windows

Biên dịch chương trình:

```powershell
gcc -std=c11 -Wall -Wextra -pedantic src/main.c src/utils.c src/transaction.c src/budget.c src/report.c src/file_io.c -Iinclude -o expense_manager.exe
```

Chạy chương trình:

```powershell
.\expense_manager.exe
```
### Cách 2: Biên dịch và chạy trong Visual Studio Code

Nếu sử dụng Visual Studio Code, có thể dùng file `.vscode/tasks.json` đã được cấu hình sẵn.

Cách thực hiện:

1. Mở thư mục project bằng Visual Studio Code.
2. Chọn menu `Terminal` -> `Run Build Task...`.
3. Chọn task build của project.
4. Sau khi build thành công, mở terminal trong VS Code và chạy file thực thi.

Trên macOS/Linux:

```bash
./expense_manager
```

Trên Windows:

```powershell
.\expense_manager.exe
```
## 6. Hướng dẫn sử dụng
Sau khi chạy chương trình, menu chính sẽ hiển thị các lựa chọn như:
1. Quan ly giao dich
2. Bao cao thong ke
3. Quan ly ngan sach
0. Thoat chuong trinh
Người dùng nhập số tương ứng với chức năng muốn thực hiện.
### 6.1. Quản lý giao dịch

Người dùng có thể thực hiện các thao tác:

- Thêm giao dịch mới.
- Xem danh sách giao dịch.
- Sửa thông tin giao dịch.
- Xóa giao dịch.
- Tìm kiếm giao dịch.

Mỗi giao dịch gồm các thông tin:

- Mã giao dịch.
- Loại giao dịch: thu hoặc chi.
- Số tiền.
- Danh mục.
- Ngày giao dịch.
- Ghi chú.

Danh sách giao dịch được sắp xếp theo ngày, giao dịch có ngày xuất hiện sớm hơn sẽ được hiển thị trước.

### 6.2. Quản lý ngân sách

Người dùng có thể thiết lập ngân sách chi tiêu cho từng danh mục theo tháng và năm.

Mỗi ngân sách gồm các thông tin:

- Danh mục.
- Tháng.
- Năm.
- Hạn mức chi tiêu.

Nếu tổng chi tiêu của một danh mục trong tháng vượt quá hạn mức đã đặt, chương trình sẽ đưa ra cảnh báo.

### 6.3. Báo cáo thống kê

Chương trình hỗ trợ thống kê theo:

- Một tháng, một năm cụ thể.
- Toàn bộ dữ liệu giao dịch.

Nội dung thống kê gồm:

- Tổng thu.
- Tổng chi.
- Số dư hiện tại.
- Thống kê khoản thu theo danh mục.
- Thống kê khoản chi theo danh mục.
- Tỷ lệ phần trăm của từng danh mục trong tổng thu hoặc tổng chi.
- Danh sách các danh mục vượt ngân sách trong kỳ.

Sau mỗi thao tác thêm, sửa hoặc xóa, dữ liệu sẽ được cập nhật và lưu lại vào file CSV.
## 7. Tác giả
KTLT - NHÓM 19 - 169312
| Họ và tên | MSSV |
|---|---|
| Bùi Tuấn Hoàng | 202419059 |
| Hoa Xuân Lộc | 202419078 |
| Vũ Quang Vinh | 202419122 |