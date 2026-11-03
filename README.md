Page Replacement Algorithms Simulator (C on Ubuntu)
Chương trình mô phỏng ba thuật toán thay thế trang FIFO, LRU và Optimal bằng ngôn ngữ C trên Ubuntu. Chương trình cho phép nhập số lượng frame, reference string, chạy riêng từng thuật toán hoặc so sánh cả ba trên cùng một bộ dữ liệu.
1. Yêu cầu môi trường
- Ubuntu Linux
- GCC
- GNU Make
- Git
- Valgrind (tùy chọn, dùng để kiểm tra quản lý bộ nhớ)
Cài đặt các công cụ:
sudo apt update
sudo apt install build-essential git make valgrind -y
Kiểm tra phiên bản:
gcc --version
git --version
make --version
valgrind --version
2. Clone project từ GitHub
git clone https://github.com/trinh2205/Implementation-and-Simulation-of-Page-Replacement-Algorithms-FIFO-LRU-and-Optimal-in-C-on-Ubuntu.git
Đi vào thư mục dự án:
cd Implementation-and-Simulation-of-Page-Replacement-Algorithms-FIFO-LRU-and-Optimal-in-C-on-Ubuntu
Nếu đã clone project trước đó, chỉ cần mở Terminal tại thư mục dự án hoặc chạy lệnh cd ở trên.
3. Biên dịch chương trình
Xóa file thực thi cũ (nếu có) và biên dịch lại:
make clean
make
Nếu biên dịch thành công, chương trình thực thi có tên:
page_simulator
Chạy chương trình:
./page_simulator
Có thể dùng lệnh sau để biên dịch và chạy theo Makefile:
make run
4. Sử dụng chương trình
Khi chạy, chương trình yêu cầu nhập theo thứ tự:
1. Số lượng frame trong bộ nhớ mô phỏng.
2. Số lượng page reference.
3. Giá trị của từng page reference, mỗi giá trị nhập tại một lời nhắc.
4. Chọn thuật toán.
Menu hiện tại:
1. FIFO    - First In First Out
2. LRU     - Least Recently Used
3. Optimal - Optimal Page Replacement
4. Compare All Algorithms
4.1. Chạy riêng FIFO
Chạy:
./page_simulator
Ví dụ dữ liệu nhập:
Enter number of frames: 3
Enter number of page references: 8
Page reference 1: 7
Page reference 2: 0
Page reference 3: 1
Page reference 4: 0
Page reference 5: 2
Page reference 6: 0
Page reference 7: 3
Page reference 8: 0
Enter your choice: 1
4.2. Chạy riêng LRU
Dùng cùng dữ liệu thử nghiệm và chọn:
Enter your choice: 2
4.3. Chạy riêng Optimal
Dùng cùng dữ liệu thử nghiệm và chọn:
Enter your choice: 3
4.4. Chạy và so sánh cả ba thuật toán
Chọn:
Enter your choice: 4
Chương trình lần lượt chạy FIFO, LRU và Optimal với cùng số frame và cùng reference string, sau đó in bảng so sánh Page Fault, Page Hit, Fault Ratio và Hit Ratio.
5. Chạy nhanh bằng dữ liệu mẫu
Có thể chuyển dữ liệu vào chương trình tự động bằng here-document, không cần nhập từng giá trị bằng tay.
Bộ dữ liệu mẫu 1
- Số frame: 3
- Số page reference: 13
- Reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2
- Lựa chọn 4: Compare All Algorithms
Chạy lệnh:
./page_simulator <<'INPUT'
3
13
7
0
1
2
0
3
0
4
2
3
0
3
2
4
INPUT
Kết quả Page Fault/Page Hit kỳ vọng:
Thuật toán	Page Faults	Page Hits
FIFO	10	3
LRU	9	4
Optimal	7	6


Bộ dữ liệu mẫu 2
- Số frame: 3
- Số page reference: 13
- Reference string: 7 0 1 0 2 0 3 0 4 0 5 0 6
- Lựa chọn 4: Compare All Algorithms
Chạy lệnh:
./page_simulator <<'INPUT'
3
13
7
0
1
0
2
0
3
0
4
0
5
0
6
4
INPUT
Đây là bộ dữ liệu thứ hai đã dùng trong quá trình kiểm thử. Với bộ dữ liệu này, kết quả Optimal có thể bằng LRU; không nên kết luận thuật toán bị lỗi chỉ vì hai thuật toán có cùng số Page Fault.
6. Kiểm tra quản lý bộ nhớ bằng Valgrind
Chạy chương trình dưới Valgrind:
valgrind --leak-check=full --show-leak-kinds=all ./page_simulator
Sau đó nhập dữ liệu và chọn thuật toán cần kiểm tra. Để kiểm tra luồng chạy so sánh, chọn 4.

Kết quả tốt cần có các dòng tương tự:
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
7. Các lệnh Git thường dùng
Xem trạng thái thay đổi:
git status
Thêm và commit thay đổi:
git add .
git commit -m "Update page replacement simulator"
Đẩy commit lên GitHub:
git push
Xem lịch sử commit:
git log --oneline
8. Dọn file thực thi và biên dịch lại
Xóa chương trình đã biên dịch:
make clean
Biên dịch lại:
make
Chạy chương trình:
./page_simulator
9. Cấu trúc thư mục
.
├── include/
│   ├── algorithms.h
│   ├── input.h
│   └── simulator.h
├── src/
│   ├── main.c
│   ├── input.c
│   ├── simulator.c
│   ├── fifo.c
│   ├── lru.c
│   └── optimal.c
├── tests/
├── docs/
├── Makefile
├── README.md
└── .gitignore
10. Chỉ số được chương trình thống kê
- Page Faults: số lần trang được yêu cầu chưa có trong frame.
- Page Hits: số lần trang được yêu cầu đã có trong frame.
- Fault Ratio: Page Faults / Total References × 100%.
- Hit Ratio: Page Hits / Total References × 100%.
Với mỗi lần chạy hợp lệ:
Page Faults + Page Hits = Total References
Fault Ratio + Hit Ratio = 100%
11. GitHub repository
Implementation and Simulation of Page Replacement Algorithms
