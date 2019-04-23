# MPM - Prefork

## Some config directives
* `StartServers`: Number of child processes created at startup
* `MaxSpareServers`: Maximum number of _idle_, which is not handling any request, child process
* `MinSpareServers`: Minimum number of _idle_ child process
* `MaxRequestWorkers`: Maximum number of child processes that will be spawned
    - Note.
        - This directive called as `MaxClients` before Apache version 2.3.13.
* `ServerLimit`: Maximum number of child processes we can configure in `MaxRequestWorkers`
    - Note.
        - You need to configure this directive only if you want to set `MaxRequestWorkers` more than 256. You shouldn't set this value higher than `MaxRequestWorkers`.
* `ListenBackLog`: Maximum length of the backlog queue. You may want to increase this value when your system is under SYN Flood attack, and so on.
    - Note.
        - In this context, backlog contains only sockets which is already established, TCP handshake is finished and is waiting accept.
        - If you want to increase this value more than 128, you must also increase `net.core.somaxconn`. For more information, please listen(2) man page.
        - You can configure the length of the queue which have incomplete sockets, TCP handshake is not finished yet, with `net.ipv4.tcp_max_syn_backlog`.

## References
* [mpm_common - Apache HTTP Server Version 2.4](https://httpd.apache.org/docs/2.4/en/mod/mpm_common.html)
* [prefork - Apache HTTP Server Version 2.4](https://httpd.apache.org/docs/2.4/en/mod/prefork.html)
