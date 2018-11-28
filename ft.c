static void init(void)
{
#ifdef _WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void end(void)
{
#ifdef _WIN32
    WSACleanup();
#endif
}

void	arg(int argc, char **argv)
{
	if (argc != 3)
	{
		printf(	"Invalide Argument.\n"
			"Usage: ./%s [ip] [port]\n", argv[0]);
		exit(0);
	}

}

int	init_connection(char **argv)
{
	int network_socket;
	int connection_status;
	char server_response[1024];

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN server_address = {0};
	struct hostent *hostinfo;

	if (network_socket == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}
	
	hostinfo = gethostbyname(argv[1]);
	if (hostinfo == NULL)
	{
		printf("Unknow host %s.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	server_address.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_family = AF_INET;

	connection_status = connect(network_socket, (SOCKADDR *) &server_address, sizeof(SOCKADDR));
	if (connection_status == SOCKET_ERROR)
	{	
		perror("connect()");
		exit(errno);
	}
	
	recv(network_socket, &server_response, sizeof(server_response), 0);

	printf("server: %s\n", server_response);

	closesocket(network_socket);
	
	return 0;
}
