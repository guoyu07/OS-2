stty
====

    stty -- set the options for a terminal device interface

`stty -a`查看当前注册终端的设置情况，需要时，这里显示的各种选择都可以重新配置。

每种终端选项都有自己的名字（如ixon），其中大多数要么被设置要么被清除。在stty中相应选项前冠以负号（-），该选项被清除（禁止）；
如果无负号，该选项被设置。当希望修改各选择的值时，应在stty命令中正确书写相应选项。如命令`$ stty -ixon`将流控制设置为OFF，而命令`$ stty ixon`则将其置为ON。

* 选项parenb使终端进行奇偶校验，-parenb则是禁止校验；
* 选项cs5、cs6、cs7和cs8分别将字符大小设为5、6、7和8比特；
* 选项300、600、1200、2400、4800、9600和19200设置波特率；
* cstopb和-cstopb分别设置两个或一个停止位；
* tabs使系统使用制表符而不是空格序列，因此减少了输出量，选项-tabs仅使用空格，当终端不能正确处理制表符（tab）时应使用该项。

stty还可用于控制一些具有特殊控制功能的键，系统可能已经使用CTRL-D作为文件结束符，但你可能喜欢使用CTRL-C。

因此可以使用stty命令改变之：
`$ stty eof c`
