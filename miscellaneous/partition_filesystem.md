# Partition/File system

## Environment
```sh
$ uname -a
Linux centos.mas9612.net 3.10.0-957.el7.x86_64 #1 SMP Thu Nov 8 23:39:32 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux
$ cat /etc/redhat-release
CentOS Linux release 7.6.1810 (Core)
```

## Partition
* hard disks can be divided into one or more logical disks: **partition**
    - division is recorded in the **partition table**

### Example
In this example, `/dev/sda` divided into two partition called `sda1` and `sda2`.

```sh
$ ll /dev/sd*
brw-rw----. 1 root disk 8,  0 May 27 23:45 /dev/sda     # sda refers the entire disk
brw-rw----. 1 root disk 8,  1 May 27 23:45 /dev/sda1    # first partition of sda
brw-rw----. 1 root disk 8,  2 May 27 23:45 /dev/sda2
brw-rw----. 1 root disk 8, 16 May 27 23:45 /dev/sdb
```

## fdisk command
fdisk command manipulates disk partition table.
It can do various operation like list/create/delete partition.

### List the partition table
```sh
$ fdisk -l [<device name>]
```

If `<device name>` given, fdisk will print information about given device.
```sh
$ fdisk -l /dev/sda

Disk /dev/sda: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x000b67da

   Device Boot      Start         End      Blocks   Id  System
/dev/sda1   *        2048     2099199     1048576   83  Linux
/dev/sda2         2099200    16777215     7339008   8e  Linux LVM
```

If `<device name>` is omitted, fdisk will read `/proc/partitions` and prints its information.
```sh
$ fdisk -l

Disk /dev/sda: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x000b67da

   Device Boot      Start         End      Blocks   Id  System
/dev/sda1   *        2048     2099199     1048576   83  Linux
/dev/sda2         2099200    16777215     7339008   8e  Linux LVM

Disk /dev/sdb: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x13cbaa39

   Device Boot      Start         End      Blocks   Id  System
/dev/sdb1            2048     8390655     4194304   83  Linux

Disk /dev/mapper/centos-root: 6652 MB, 6652166144 bytes, 12992512 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes


Disk /dev/mapper/centos-swap: 859 MB, 859832320 bytes, 1679360 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
```

### `/proc/partitions`
* contains partition tables
* fields
    - major number: represents the device type
    - minor number
    - number of blocks
    - device name

Major/Minor number is documented in the Documentation/admin-guide/devices.txt in the Linux kernel source tree.

### Primary/Extended partition
* Primary partition: ordinary partition
* Extended partition: this type of partition has logical partition to extend limit of number of partition. In logical partition, we can create another partition as same as physical hard drive.

MBR (Master Boot Record) can have only four partition.
To create more than four partition, we must use extended partition instead of primary partition.

### Create new partition
Use `n` command in the fdisk utility to create new partition.

Note that changes will not commited until we run `w` command in fdisk utility.
We can cancel partition creation with `q` command after run `n` command if we haven't run `w` command yet.

#### Example
```sh
$ fdisk /dev/sdb
Welcome to fdisk (util-linux 2.23.2).

Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.


Command (m for help): n
Partition type:
   p   primary (1 primary, 0 extended, 3 free)
   e   extended
Select (default p): p   # create primary partition
Partition number (2-4, default 2):
First sector (2099200-16777215, default 2099200):
Using default value 2099200
Last sector, +sectors or +size{K,M,G} (2099200-16777215, default 16777215): +2G     # partition size is 2GB
Partition 2 of type Linux and of size 2 GiB is set

Command (m for help): p     # check result

Disk /dev/sdb: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x13cbaa39

   Device Boot      Start         End      Blocks   Id  System
/dev/sdb1            2048     2099199     1048576   83  Linux
/dev/sdb2         2099200     6293503     2097152   83  Linux

Command (m for help): w     # commit changes
The partition table has been altered!

Calling ioctl() to re-read partition table.
Syncing disks.
```

### Delete partition
Use `d` command in the fdisk utility to delete partition.

#### Example
```sh
$ fdisk /dev/sdb
Welcome to fdisk (util-linux 2.23.2).

Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.


Command (m for help): d
Partition number (1,2, default 2): 1    # delete partition 1
Partition 1 is deleted

Command (m for help): p

Disk /dev/sdb: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x13cbaa39

   Device Boot      Start         End      Blocks   Id  System
/dev/sdb2         2099200     6293503     2097152   83  Linux

Command (m for help): w
The partition table has been altered!

Calling ioctl() to re-read partition table.
Syncing disks.
```

### Expand partition size
To expand existing partition, we should do following:

1. Check current partition table
1. Delete partition which want to expand
1. Recreate partition with larger size

Note:
We must check current partition table before delete partition.
When recreate partition, previous start sector is required. Otherwise, some data may lost.

```sh
$ fdisk /dev/sdb
Welcome to fdisk (util-linux 2.23.2).

Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.


Command (m for help): p

Disk /dev/sdb: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x13cbaa39

   Device Boot      Start         End      Blocks   Id  System
/dev/sdb1            2048     2099199     1048576   83  Linux   # start sector is 2048

Command (m for help): d
Selected partition 1
Partition 1 is deleted

Command (m for help): n     # recreate partition
Partition type:
   p   primary (0 primary, 0 extended, 4 free)
   e   extended
Select (default p): p
Partition number (1-4, default 1):
First sector (2048-16777215, default 2048):     # if this value is not same as previous start sector (in this example 2048), we must type it manually.
Using default value 2048
Last sector, +sectors or +size{K,M,G} (2048-16777215, default 16777215): +4G
Partition 1 of type Linux and of size 4 GiB is set

Command (m for help): p

Disk /dev/sdb: 8589 MB, 8589934592 bytes, 16777216 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk label type: dos
Disk identifier: 0x13cbaa39

   Device Boot      Start         End      Blocks   Id  System
/dev/sdb1            2048     8390655     4194304   83  Linux

Command (m for help): w
The partition table has been altered!

Calling ioctl() to re-read partition table.
Syncing disks.
```

## File system
> In computing, a file system or filesystem controls how data is stored and retrieved.

Quoted from [File system - Wikipedia](https://en.wikipedia.org/wiki/File_system).

### Create Ext4 file system
```sh
$ mkfs.ext4 /dev/sdb1
mke2fs 1.42.9 (28-Dec-2013)
Filesystem label=
OS type: Linux
Block size=4096 (log=2)
Fragment size=4096 (log=2)
Stride=0 blocks, Stripe width=0 blocks
65536 inodes, 262144 blocks
13107 blocks (5.00%) reserved for the super user
First data block=0
Maximum filesystem blocks=268435456
8 block groups
32768 blocks per group, 32768 fragments per group
8192 inodes per group
Superblock backups stored on blocks:
        32768, 98304, 163840, 229376

Allocating group tables: done
Writing inode tables: done
Creating journal (8192 blocks): done
Writing superblocks and filesystem accounting information: done
```

### Expand file system size
Note:
Before run the following command, make sure that partition has sufficient size.

```sh
$ fsck.ext4 -f /dev/sdb1    # check file system if required
e2fsck 1.42.9 (28-Dec-2013)
Pass 1: Checking inodes, blocks, and sizes
Pass 2: Checking directory structure
Pass 3: Checking directory connectivity
Pass 4: Checking reference counts
Pass 5: Checking group summary information
/dev/sdb1: 12/65536 files (0.0% non-contiguous), 12956/262144 blocks

$ resize2fs /dev/sdb1
resize2fs 1.42.9 (28-Dec-2013)
Resizing the filesystem on /dev/sdb1 to 1048576 (4k) blocks.
The filesystem on /dev/sdb1 is now 1048576 blocks long.

$ mount /dev/sdb1 /mnt/study

$ df -hT
Filesystem              Type      Size  Used Avail Use% Mounted on
/dev/mapper/centos-root xfs       6.2G  1.6G  4.7G  26% /
devtmpfs                devtmpfs  484M     0  484M   0% /dev
tmpfs                   tmpfs     496M     0  496M   0% /dev/shm
tmpfs                   tmpfs     496M  6.8M  489M   2% /run
tmpfs                   tmpfs     496M     0  496M   0% /sys/fs/cgroup
/dev/sda1               xfs      1014M  132M  883M  13% /boot
tmpfs                   tmpfs     100M     0  100M   0% /run/user/1000
tmpfs                   tmpfs     100M     0  100M   0% /run/user/0
/dev/sdb1               ext4      4.0G  4.0M  3.7G   1% /mnt/study
```

## References
* [https://www.kernel.org/doc/Documentation/admin-guide/devices.txt](https://www.kernel.org/doc/Documentation/admin-guide/devices.txt)
* [E.2.5. /proc/devices - Red Hat Customer Portal](https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/6/html/deployment_guide/s2-proc-devices)
* [E.2.23. /proc/partitions - Red Hat Customer Portal](https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/6/html/deployment_guide/s2-proc-partitions)
* [How to Grow an ext2/3/4 File System with resize2fs - Red Hat Customer Portal](https://access.redhat.com/articles/1196353)
