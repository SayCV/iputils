#include <string.h>
#include "ping_common.h"

/* default to ipv4 */
int (*send_probe)(void) = send_probe4;
int (*receive_error_msg)(void) = receive_error_msg4;
int (*parse_reply)(struct msghdr *msg, int len, void *addr, struct timeval *) = parse_reply4;
void (*install_filter)(void) = install_filter4;
int use_ipv6 = 0;
int *maxpacket = &maxpacket4;

int main(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-6")) {
			use_ipv6 = 1;
			break;
		}
	}

	if (use_ipv6) {
		send_probe = send_probe6;
		receive_error_msg = receive_error_msg6;
		parse_reply = parse_reply6;
		install_filter = install_filter6;
		maxpacket = &maxpacket6;
		return ping6(argc, argv);
	}
	return ping4(argc, argv);
}
