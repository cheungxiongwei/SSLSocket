SSLSocket

SSLSocket 通常可以用来加密传输数据，例如 `trojan-qt` 代理。

* SSLClient
* SSLServer

如何生成测试证书？

```shell
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes
```

> Common Name 字段填写域名（domain），本地测试通常使用填写 `localhost`。

> 更多参考  
> https://codereview.qt-project.org/c/qt/qtbase/+/188321/
> https://docs.huihoo.com/qt/solutions/4/qtsslsocket/index.html
> https://stackoverflow.com/questions/39302049/connecting-qsslsocket-with-openssl-server