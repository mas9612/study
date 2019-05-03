# iptables

## List all rules
```sh
$ iptables [-t <table>] [-n] [--line-numbers] -L [<chain name>]
```

* `-L`: List all rules
* `-t <table>`: Specify a table name
    - e.g.) `iptables -t nat -L`
* `-n`: Don't resolve IP address to domain name
* `--line-numbers`: Print also line numbers
* `<chain name>`: Print only specified chain rules
    - e.g.) `iptables -L INPUT`

### Example
```sh
$ iptables -L
Chain INPUT (policy ACCEPT)
target     prot opt source               destination

Chain FORWARD (policy ACCEPT)
target     prot opt source               destination

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination

$ iptables -L INPUT
Chain INPUT (policy ACCEPT)
target     prot opt source               destination
```

## Set default policy for chain
```sh
$ iptables -P <chain> <target>
```

* `<chain>`: target chain name
* `<target>`: target (either `ACCEPT` or `DROP`)

### Example
```sh
# check initial state
$ iptables -L
Chain INPUT (policy ACCEPT)
target     prot opt source               destination

Chain FORWARD (policy ACCEPT)
target     prot opt source               destination

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination

# set INPUT chain's default policy to DROP
$ iptables -P INPUT DROP
$ iptables -L INPUT
Chain INPUT (policy DROP)
target     prot opt source               destination
```

## Add/Remove simple rule
```sh
# add rule
$ iptables -A <chain> <rule>

# remove rule
$ iptables -D <chain> <rule>|<rulenum>
```

* `-A`: append new rule to the end of the chain
* `-D`: delete the specified rule from the chain
* `-p`: the protocol of the rule
* `-s`, `--source`: source address of the rule
* `-j`: the target of the rule

### Example
```sh
# allow any tcp traffic from 192.168.56.1
$ iptables -A INPUT -p tcp --source 192.168.56.1 -J ACCEPT

# delete rule 1 from INPUT chain
$ iptables -D INPUT 1
```

## Specify rule based on TCP/UDP port number
* `-m <match>`: enable `<match>` extension
* `--sport port[:port]`: source port (can be range)
* `--dport port[:port]`: destination port (can be range)

### Example
```sh
# allow incoming tcp traffic that destination port is 80
$ iptables -A INPUT -p tcp -m tcp --dport 80

# allow outgoing udp traffic that destination port is 53
$ iptables -A OUTPUT -p udp -m udp --dport 53
```

## Define rule based on connection state
* `--state <state>`: connection state

### Example
```sh
$ iptables -A INPUT -p tcp -m state --state ESTABLISHED,RELATED
```

## References
* iptables(8)
* ipatbles-extensions(8)
