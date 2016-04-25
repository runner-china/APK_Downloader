#APK爬虫
简介：本程序是通过分析Web页面并利用`curl `& `wget`工具对安卓应用商店（https://apkpure.com/app）的APK进行爬取。  



##程序结构
- `GetAppMetadata.bat`：爬取apkpure网站中APP信息，如APK的名字、大小、APK下载地址等，并将这些元数据保存在pages目录下名为AppMetadata前缀的csv文件、txt文件中。`GetAppMetadata.exe`有2个参数，参数1是要抓取的category，参数2是要抓取的category下的页面数量（范围1-10）。

- `Download_APK.bat`：调用wget工具下载APK，下载后的APK存放在apks目录下面。需要注意一点，用wget下载下来的APK文件名后缀非.apk，但是文件内容的确是APK文件，文件名可以自己改过来。

##其他补充说明
###24种category：
books\_and\_reference  
business  
comics  
communication  
education  
entertainment  
finance  
health\_and\_fitness  
libraries\_and\_demo  
lifestyle  
media\_and\_video  
medical  
music\_and\_audio  
news\_and\_magazines  
personalization  
photography  
productivity  
shopping  
social  
sports  
tools  
transportation  
travel\_and\_local  
weather  

###AppMetadata文件的处理：
- 对于得到AppMetadata前缀的csv文件、txt文件，可以自行根据需要进行处理。例如可以写一个程序将5MB以内的apk的下载地址过滤出来，得到一个DownloadList，再调用Download_APK.bat。
- 当然也可以将csv文件导入到数据库，在数据库内进行一些处理。