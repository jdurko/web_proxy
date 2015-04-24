#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <pthread.h>
#include <sstream>
#include <utility>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>      // Needed for the socket functions
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
 #include <errno.h>
 #include <sys/stat.h>  //needed for open
#include <fcntl.h>     //needed for open
#define BACKLOG	10
#define BUF_SIZE	1024
#define LISTEN_PORT 8888
#define HTTP_PORT	80

using namespace std;
//#define SERVER_IP   "0.0.0.0"
int threadCount = BACKLOG; // total number of users the server will allow communication
void *client_handler(void *arg);
int main(int argc, char *argv[]) {
	// Declaration of variables for socket programing
	int status, *sock_tmp;
	pthread_t a_thread;
	void *thread_result;
	struct sockaddr_in addr_mine;
	struct sockaddr_in addr_remote;
	int sock_listen;
	int sock_aClient;
	int addr_size;
	int reuseaddr = 1;

	//Socket binding
	sock_listen = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen < 0) {
		perror("socket() failed");
		exit(0);
	}
	// Address settings includind IP, PORT NUMBER
	memset(&addr_mine, 0, sizeof(addr_mine));
	addr_mine.sin_family = AF_INET;
	addr_mine.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_mine.sin_port = htons((unsigned short)LISTEN_PORT);
	//Check Port number status
	status = bind(sock_listen, (struct sockaddr *) &addr_mine,
		sizeof(addr_mine));
	if (status < 0) {
		perror("bind() failed");
		close(sock_listen);
		exit(1);
	}
	// Listen port number
	status = listen(sock_listen, 5);
	if (status < 0) {
		perror("listen() failed");
		close(sock_listen);
		exit(1);
	}

	addr_size = sizeof(struct sockaddr_in);
	printf("waiting for a client\n");
	//Thread Creation block
	//while (1) {
		if (threadCount < 1) {
			sleep(1);
		}

		sock_aClient = accept(sock_listen, (struct sockaddr *) &addr_remote,
			(socklen_t*)&addr_size);
		if (sock_aClient == -1){
			close(sock_listen);
			exit(1);
		}

		printf("Got a connection from %s on port %d\n",
			inet_ntoa(addr_remote.sin_addr),
			htons(addr_remote.sin_port));
		sock_tmp = (int*)malloc(1);
		*sock_tmp = sock_aClient;
		printf("thread count = %d\n", threadCount);
		threadCount--;
		status = pthread_create(&a_thread, NULL, client_handler,
			(void *)sock_tmp);
		if (status != 0) {
			perror("Thread creation failed");
			printf("In client_handler ERROR \n");
			close(sock_listen);
			close(sock_aClient);
			free(sock_tmp);
			exit(1);
		}
		while(1){
            continue;
		}
	//}
	return 0;


}
// function each created thread compute
void *client_handler(void *sock_desc) {
    // 3. Define a table of blocking websites records using an STL map
std::map<int, std::string> g_mapwebRecords;
            g_mapwebRecords.insert(std::pair<int, std::string> (1, "www.facebook.com") );//insert
			g_mapwebRecords.insert(std::pair<int, std::string> (2, "www.youtube.com") );//insert
			g_mapwebRecords.insert(std::pair<int, std::string> (3, "www.hulu.com") );//insert
			g_mapwebRecords.insert(std::pair<int, std::string> (4, "www.virus.com") );//insert
int msg_size,j;
	char buf[BUF_SIZE],line[1];
	//int text;
	int sock = *(int*)sock_desc; //socket initialization
	char *token;
	std::string buf1;
	int loop=1;
	string see="GE";
while(1){
	if (recv(sock, buf, BUF_SIZE, 0)<0){
		//ERROR_RESPONSE
	}
	if (strcmp(buf,see.c_str())==0){
		//close(sock);
        loop=0;
        close(sock);
        exit(1);
		//free(sock_desc);
	}
	if(loop==1){
	printf(" FIRST THING FIRST %s\n", buf);
	/* get the first token */
	token = strtok(buf, "/ HTTP");
	printf(" SECOND THING FIRST %s\n", token);
	/* walk through other tokens */

		token = strtok(NULL, "/ HTTP");

		bool exist,checkin = false;
		std::string extension = ".txt";
        std::string extension1="";
		int len = strlen(token) + extension.length()+1;
		int len1=strlen(token)+extension1.length()+1;
        char weblink[len1];
		char  url[len];
		strcpy(weblink,token);
		strcpy(url, token);
		 strcat (url,extension.c_str());
		 strcat (weblink,extension1.c_str());
		 printf(" THIRD THING FIRST %s\n", url);
		// allocate memory to contain file data
		char* buffer = new char[BUF_SIZE];
		//std::ifstream ifs(url, std::ifstream::binary);
        std::ifstream infile(url);

		// get pointer to associated buffer object
		//std::filebuf* pbuf = infile.rdbuf();
		if (infile.good()==false){
			exist = false;
			printf(" EXIST FIRST-FALSE %d\n", exist);
		}
		else{
			exist = true;
			printf(" EXIST FIRST-TRUE %d\n", exist);
		}

		//File exist in cache
		if (exist == true){
          msg_size= open(url, O_RDWR);
           printf(" CACHED OPEN ERRNO %d\n", errno);
     while (read(msg_size,line,1)>=0)
    {
     j=write(sock,line,1);


     }

  infile.close();
  j=close(msg_size);
close(sock);
//free(sock_desc);
		}
		//file not in cache
		if (exist == false){
    for (std::map<int, std::string>::iterator it = g_mapwebRecords.begin(); it != g_mapwebRecords.end(); ++it)
    {
       std::cout<<  it->second.c_str() << "  value of checkin true"<<'\n';
//		if(it->second.c_str()==token){
//			checkin==true;
//		}
        if(strcmp(it->second.c_str(),weblink)==0){
			checkin==true;
			string block="blocking.text";
			strcpy(weblink,block.c_str());
			msg_size= open("blocking.text", O_RDWR);
           printf(" CACHED OPEN ERRNO %d\n", errno);
     while (read(msg_size,line,1)>=0)
    {
     j=write(sock,line,1);

     }
     close(sock);
//     free(sock_desc);
     break;
		}

    }
	if(checkin==false){
			int sock_send;
			struct sockaddr_in	addr_send ;
			struct addrinfo hints,*servinfo,*p;
			int	i, text;
			int	send_len, bytes_sent;
			char  buff[BUF_SIZE];//contain temporary file name request
			//TODO CONNECT TO HTTP 80
			int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
//int sock;
struct sockaddr_in client;
int PORT = 80;
			/* Obtain address(es) matching host/port */

          struct hostent * host = gethostbyname(weblink);

    if ( (host == NULL) || (host->h_addr == NULL) ) {
        cout << "Error retrieving DNS information." << endl;
        close(sock);
        close(sock_send);
        //free(sock_desc);
        exit(1);
    }

    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    memcpy(&client.sin_addr, host->h_addr, host->h_length);

    sock_send = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_send < 0) {
        cout << "Error creating socket." << endl;
        close(sock_send);
        close(sock);
        exit(1);
    }

    if ( connect(sock_send, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock_send);
        close(sock);
        cout << "Could not connect" << endl;
        exit(1);
    }



//			 // allocate memory for file content

  stringstream ss;
    ss << "GET / HTTP/1.1\r\n"
       << "host:"<<weblink<<"\r\n"
       << "Accept: text/html,application/json\r\n"
       << "\r\n\r\n";
    string request = ss.str();

    if (send(sock_send, request.c_str(), request.length(), 0) != (int)request.length()) {
        cout << "Error sending request." << endl;
        exit(1);
    }

    char cur[5];
        std::streambuf *psbuf1, *backup1;
 	 std::fstream filestr1;
 	// int fdB = open(url, O_CREAT | O_RDWR, 0644);
 	 filestr1.open(url,std::fstream::in | std::fstream::out | std::fstream::app);

    while ( read(sock_send,cur, 5) >= 0 ) {
        //cout << cur;
         filestr1<<cur;
         text=write(sock,cur,5);


    }
// char cur[1];
printf(" TEST 1 ERRNO %d\n", errno);
close(sock_send);
printf(" TEST 2 ERRNO %d\n", errno);
 //close(sock);
//free(sock_desc);
			//send a connection request

}
if(checkin==true){
//   "blocking web content";
printf(" Blocking website \n");
   msg_size= open("blocking.text", O_RDWR);
           printf(" CACHED OPEN ERRNO %d\n", errno);
     while (read(msg_size,line,1)>=0)
    {
     j=write(sock,line,1);


     }

	}

close(sock);
//free sock
threadCount++;
}
}
}
}
