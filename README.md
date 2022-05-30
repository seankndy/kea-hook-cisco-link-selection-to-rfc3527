This Kea hook creates the RFC3527 "link-selection" RAI sub-option 5 from Cisco's proprietary link-selection sub-option 150.

Kea natively uses the RFC3527 sub-option during subnet selection, but it does not use Cisco's sub-option 150.  So this hook copies the value from sub-option 150 into sub-option 5 (so long as sub-option 5 didn't already exist).  This saves you from having to create a custom client-class that matches Cisco's sub-option 150 for every subnet.


Installation on Ubuntu:

```
$ sudo apt-get install g++ make isc-kea-dev libboost-dev libboost-system-dev
$ make
$ sudo make DESTDIR=/usr/lib/x86_64-linux-gnu/kea/hooks install
```

Then add the hook to your kea-dhcp4.conf:

     "hook-libraries": [
         // ....
         {
             "library": "/usr/lib/x86_64-linux-gnu/kea/hooks/libdhcp_cisco_link_selection_to_rfc3527.so"
         }
         // ....
     ]
