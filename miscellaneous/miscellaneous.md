# Miscellaneous

## umask
When we create new file, its permission is controled with umask.

The permission of new file is calculated with the following formula:
```
(File permission) = (Requested permission) - (umask)
```

Default permission is `0777` for directory, `0666` for normal file.
They will used with umask to calculate the real permission.

### Check/Set umask
To check the current umask, use umask command without argument.
```sh
$ umask
0002
```

To set umask, pass new umask as umask command's argument.
```sh
$ umask 0022

# check new umask
$ umask
0022
```

### Example
* User requested permission: `0666`, umask: `0022`
    - -> Permission: `0644`
