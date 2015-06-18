#メディアサーバとの通信方法

## 【Introduction】 ##

  1. モニタリング部分
  1. メディアサーバ部分
  1. 通信方法


## 【Details】 ##

### モニタリング部 ###
開発環境
  * Visual Studio 2010 (C++)
  * .NET Framework 4.0
  * DirectShow


---

### サーバ部 ###
あ、あとから書くよっ！


---

### 通信方法 ###
|送信データ|プロトコル|ライブラリ|
|:--------------|:--------------|:--------------|
|メディア   |RTP            |http://sourceforge.jp/projects/sfnet_rtp-lib/<br> <a href='http://www.streamcoders.com/products/rtpnet.html'>http://www.streamcoders.com/products/rtpnet.html</a>
<tr><td>コマンド   </td><td>TCP            </td><td><a href='http://msdn.microsoft.com/ja-jp/library/system.net.sockets.tcplistener.aspx'>System.Net.Sockets.TcpListener</a><br> <a href='http://msdn.microsoft.com/ja-jp/library/system.net.sockets.tcpclient.aspx'>System.Net.Sockets.TcpClient</a></td></tr>