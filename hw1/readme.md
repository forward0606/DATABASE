---
tags: DB
---
<style>
    H1{
        text-align: center;  /* 題目置中 */
    }
    H4{
        text-align: right;  /* 題目置中 */
    }
    blockquote > P {    /* Blockquote 取消第一行兩格*/
        text-indent: 0;
    }
    .markdown-body > h4 {   /* 讓限制那行離上面近一點 */
        padding: 0;
        margin: 0;
    }
    .markdown-body > h1 {
        border-bottom: 0;
        padding: 0;

    }
</style>


# HW1 Report
#### 409410050 資工二 王謙靜
## MYSQL
### 如何建立 MySQL database
1. 打開CMD，移動路徑到```C:\Program Files\MySQL\MySQL Server 8.0\bin```
2. 輸入指令```mysql --user=root --password```，並輸入密碼登入，登入成功後會看到提示文字變成```mysql>```，代表進入操作資料庫的模式
3. 輸入指令```CREATE DATABASE db_name;```，其中```db_name```為database的名稱
4. 以下為此過程的截圖
![database setting](https://i.imgur.com/yZEkojQ.png)

5. 檢查database有誰：`show databases;`
### 如何建立 MySQL table
1. 輸入```use db_name;```，來使用```db_name```這個datebase
2. 建立table的語法為
    ```sql
    CREATE TABLE 資料表名 (欄位1 資料型態, 欄位2 資料型態, ......);
    ```
    下方指令可用來設定一個名為`Product`的資料庫，指定其有四個欄位分別為`pNo, pName, unitPrice, category`，後面的`varchar`和`int`為欄位的data type`varchar(n)`為一個長度為`n`字串，`int`為整數，而在`pNo`後方的`PRIMARY KEY`則表示將`pNo`設為primary key

    ```sql
    CREATE TABLE `Product` (
      `pNo` varchar(7) PRIMARY KEY,
      `pName` varchar(50),
      `unitPrice` int,
      `category` varchar(50));
    ```
3. 將資料插入table的語法為
   ```sql
   INSERT INTO 資料表(欄位1,欄位2,......)
   VALUES(值1,值2,......),(值1,值2,......), ........;
   ```
   下方指令可用來將資料存入table(已存入第一筆資料為例)，`Product`為table名稱，後方的括號依序為其欄位名稱，`VALUES`後接的是要存入資料的值
    ```sql
    INSERT INTO Product (pNo, pNamem, unitPrice, category)
    VALUES('b30999', '資料庫理論與實務', 500, 'Book');
    ```
    也可以一次存入多筆資料
    ```sql
    INSERT INTO Product (pNo, pNamem, unitPrice, category)
    VALUES('b30999', '資料庫理論與實務', 500, 'Book'),
    ('d11222', '任賢齊專輯三', 300, 'CD');
    ```
4. 以下為此過程的截圖
![](https://i.imgur.com/cXeu1cb.png)

    ![](https://i.imgur.com/HZyY2zH.png)
### 顯示各table的完整內容/每筆資料
輸入指令來檢查目前table的資料

```sql
SELECT * FROM db_name.table_name;
```

**product:**
![](https://i.imgur.com/SaQ7HmR.png)
**record:**
![](https://i.imgur.com/4dWdS3u.png)

###  MySQL查詢結果的完整截圖
查詢1：找出定價400元以下所有CD。列出商品名稱、定價。
    ![](https://i.imgur.com/sTBsUzj.png)
查詢2：找出所有定價比所有書籍都高的商品。
    ![](https://i.imgur.com/VzTXG1v.png)
查詢3：找出最優惠的交易記錄。列出交易編號、該筆交易得到的優惠金額。
    ![](https://i.imgur.com/zbgPIGD.png)


## MongoDB
### 如何建立 MongoDB database
1. 在CMD輸入 `mongo`，進入mongoDB的操作模式
2. 輸入 `use db_name`，選擇使用的database名稱，若db_name不存在則會新增一個database
3. 使用指令 `show dbs` 檢查是否成功新增(若database還沒有任何操作，則指令 `show dbs` 出現的結果將不會有該database，可在有insert之後查看是否有新增database)
4. 以下為此過程的截圖
![](https://i.imgur.com/2e2qlnG.png)

### 如何建立 MongoDB table
在mongoDB中insert會進一個table有兩種情況:若table已存在，insert會直接將資料放入table中；若table不存在，insert則會新增一個table在database中，之後再insert資料進table中。

insert 一筆資料
```sql
db.table_name.insertOne( {欄位1: 值1, 欄位二: 值2, ...} )
```
insert 多筆資料
```sql
db.table_name.insertMany([
    {欄位1: 值1, 欄位二: 值2, ...},
    {欄位1: 值1, 欄位二: 值2, ...}, ...
])
```
**Product**
![](https://i.imgur.com/tpT7Mwu.png)

**Record**
![](https://i.imgur.com/iTaaeqm.png)



### table的完整內容
查看database裡的table
```sql
show collections
```

查看table內容
```sql
db.table_name.find()
```
![](https://i.imgur.com/J5mnFCo.png)

### MongoDB查詢結果
查詢1：找出定價400元以下所有CD。列出商品名稱、定價。
![](https://i.imgur.com/L7jS10C.png)
查詢2：找出所有定價比所有書籍都高的商品。
![](https://i.imgur.com/tWgQvhg.png)
查詢3：找出最優惠的交易記錄。列出交易編號、該筆交易得到的優惠金額。
![](https://i.imgur.com/7Y6deYb.png)


## 狀況排解
### 中文字產生'?'
![問題1-2](https://i.imgur.com/ul2TOo9.png)
**解決:**
在CMD輸入指令，將CMD輸入時的中文編碼從```Big5```改成```utf-8```
```
chcp 65001
```

## Reference

[mysql語法-1](https://www.cynet.com.tw/learning/MySql/Page04.htm)
[mysql語法-2](https://www.mysql.tw/2015/05/select-sql.html)
[環境變數設定](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/)
[mongodb-1](https://docs.mongodb.com/manual/reference/method/db.collection.insertMany/)
[mongodb-2](https://zh-tw.coderbridge.com/series/800ffff9f7524d35ac6ecc51fffda4b9/posts/fccb25a652444dfda38629965eac7c7d)
[mongodb-3](http://dog0416.blogspot.com/2015/08/databasemongodb-1-crud-operation-1.html)
[mongodb-4](https://docs.mongodb.com/manual/reference/method/db.dropDatabase/)

