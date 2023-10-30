# csc10003-crossy-road

Cách hoạt động của trò chơi

Ở mỗi màn chơi, trò chơi sẽ có 1 bản đồ kích thước 32x18.

Mỗi hàng của bản đồ được gọi là một Row. Một Row có thể là vỉa hẻ, đường nhựa hoặc sông. Mỗi Row có thể có một số lượng các vật thể khác nhau.

1. Vỉa hè

Các vật cản ở vỉa hè sẽ đứng im, chỉ có tác dụng chắn đường không cho người chơi tiến vào đó.

2. Đường nhựa

Mỗi một khoảng thời gian, trò chơi sẽ chạy hàm kiểm tra xem người chơi đã bị xe tông hay chưa. 

- Nếu người chơi chưa bị tông, update vị trí của tất cả các xe.
- Ngược lại, kết thúc game.

3. Sông

Mỗi một khoảng thời gian, trò chơi sẽ chạy hàm kiểm tra xem người chơi có đang ở trên khúc gỗ nào không.

- Nếu có, cho người chơi trôi theo khúc gỗ. Nếu vượt ra khỏi phạm vi màn hình, kết thúc game.
- Ngược lại, kết thúc game.