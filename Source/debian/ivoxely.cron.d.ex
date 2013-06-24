#
# Regular cron jobs for the ivoxely package
#
0 4	* * *	root	[ -x /usr/bin/ivoxely_maintenance ] && /usr/bin/ivoxely_maintenance
