# Apache

## MPM (Multi-Processing Module)
* [Prefork](mpm-prefork.md): multi-process strategy

### How to determine the current MPM type
```sh
$ httpd -V | grep MPM
Server MPM:     prefork
```

## Security considerations
### For DoS attack
We can configure several directive to mitigate the affect of DoS attack.

* `TimeOut`: Set timeout for waiting some I/O
* `RequestReadTimeout`: Set timeout for completing TLS handshake, receiving request headers and body.
    - mod_reqtimeout is required to use this directive
* `KeepAliveTimeout`: Set timeout for waiting subsequent request

#### mod_dosdetector
This module sets the environment variable when detect DoS attack.
We can take appropriate action if it sets (e.g. Limit connection).

#### References
* [core - Apache HTTP Server Version 2.4](https://httpd.apache.org/docs/2.4/en/mod/core.html)
* [mod_reqtimeout - Apache HTTP Server Version 2.4](https://httpd.apache.org/docs/2.4/mod/mod_reqtimeout.html)
* [stanaka/mod_dosdetector: An apache module for detecting DoS attacks](https://github.com/stanaka/mod_dosdetector)
