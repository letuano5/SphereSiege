# SphereSiege
(cuộc vây hãm của các tinh thể)

## Giới thiệu
Dựa vào một chủ đề cổ điển, là khi tàu vũ trụ di chuyển trên không gian sẽ gặp phải những tinh thể không xác định bay xung quanh. Để tránh va chạm, ta cần "xử lý" các tinh thể này, trước khi bị chúng va phải.

## Cách chơi
- Bạn sẽ được cho một tàu chiến với vô hạn lượng đạn. Nhiệm vụ của bạn là phải di chuyển xung quanh map để tiêu diệt hết toàn bộ kẻ địch.
- Mỗi màn chơi sẽ có một số lượt, và mỗi lượt sẽ có một số nhân vật địch được sinh ra. Bạn cần tiêu diệt hết toàn bộ nhân vật địch này để qua lượt, cũng như chơi hết số lượt của màn chơi này để sang đến màn chơi khác. Sau mỗi màn chơi, số lượt sẽ tăng dần và số loại địch sẽ đa dạng hơn.
- Các màn chơi sẽ được sinh ra liên tục, và người chơi sẽ được chơi thoải mái cho đến khi hết máu và thua cuộc.

### Phím tắt
- Điều hướng: W/A/S/D hoặc lên/xuống/trái/phải
- F: tự động bắn
- P: tạm dừng
- Esc: đóng

## Thông số game

### Hero
- Hướng bắn của tàu sẽ được tính dựa trên vị trí tương đối giữa tàu và con trỏ chuột hiện tại

### Enemy
- Mỗi enemy được đặc trưng bởi các thuộc tính: kích thước, tốc độ di chuyển, hướng di chuyển, sát thương gây ra và lượng điểm nhận được khi ta tiêu diệt chúng.
- Có 4 loại enemy chính: bình thường, nhỏ, khổng lồ, và phân bào (là loại khổng lồ nhưng có thể tự phân chia sau khi bị tách ra).
- Đặc biệt, có một loại enemy có thể săn đuổi và dí đến cùng, thay vì chỉ di chuyển theo một hướng bất kì. Xác suất để sinh ra một con loại này là $\frac{1}{50}$
- Enemy sẽ luôn di chuyển trong bản đồ cho đến khi bị giết. Khi di chuyển đến góc, chúng sẽ tự động bật ngược trở lại.

### Items
- Là các vật thể được tiếp tế để buff sức mạnh cho "main chính".
- Có các loại vật thể sau đây:
  - Tăng tốc độ bắn
  - Làm chậm kẻ địch
  - Thay thành súng ba nòng
  - Cho phép đạn bay xuyên kẻ địch
  - Tạo giáp
- Các vật thể sẽ xuất hiện ngẫu nhiên và trôi lơ lửng trên bản đồ. Khi ta ăn được các item này, các hiệu ứng sẽ được áp dụng trong vòng $5$ giây.
- Giả sử ta nhận được nhiều loại vật phẩm khác nhau, thì tất cả các hiệu ứng trên các vật phẩm này sẽ được áp dụng. Nếu ta nhận được hai vật phẩm có loại giống nhau, thì thời gian áp dụng hiệu ứng sẽ được tính theo vật phẩm được ăn cuối cùng.
