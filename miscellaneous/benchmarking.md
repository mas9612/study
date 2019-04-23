# Benchmarking

## Web server
### Apache Bench
* [ab - Apache HTTP server benchmarking tool - Apache HTTP Server Version 2.4](https://httpd.apache.org/docs/2.4/programs/ab.html)

#### Most Simple Example
```sh
$ ab http://www.example.com/
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking www.example.com (be patient).....done


Server Software:        Apache/2.4.6
Server Hostname:        www.example.com
Server Port:            80

Document Path:          /
Document Length:        4897 bytes

Concurrency Level:      1
Time taken for tests:   0.002 seconds
Complete requests:      1
Failed requests:        0
Non-2xx responses:      1
Total transferred:      5168 bytes
HTML transferred:       4897 bytes
Requests per second:    563.70 [#/sec] (mean)
Time per request:       1.774 [ms] (mean)
Time per request:       1.774 [ms] (mean, across all concurrent requests)
Transfer rate:          2844.91 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        1    1   0.0      1       1
Processing:     1    1   0.0      1       1
Waiting:        1    1   0.0      1       1
Total:          2    2   0.0      2       2
```

This command generates only one HTTP request and reports the result.

#### Specify the number of requests Apache Bench will generate
We can generate an arbitrary number of requests during benchmarking.
To set the number of requests, use `-n` option.

```sh
# generate 10000 requests
$ ab -n 10000 http://www.example.com/
```

#### Specify the concurrency of requests
We can increase the concurrency of requests with `-c` option.
```sh
$ ab -c 100 -n 10000 http://www.example.com/
```
