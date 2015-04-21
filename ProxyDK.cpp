#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <pthread.h>
#include <utility>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define BACKLOG	10
#define BUF_SIZE	1024
#define LISTEN_PORT 8888
#define HTTP_PORT	80
#define SERVER_IP   "129.120.151.94"

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
	while (1) {
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
	}
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
int msg_size;
	char buf[BUF_SIZE];
	//int text;
	int sock = *(int*)sock_desc; //socket initialization
	char *token;
	std::string buf1;
while(1){
	if (recv(sock, buf, BUF_SIZE, 0)<0){
		//ERROR_RESPONSE
	}
	if (strcmp(buf,"")==0){
		close(sock);
	}
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
		std::ifstream ifs(url, std::ifstream::binary);

		// get pointer to associated buffer object
		std::filebuf* pbuf = ifs.rdbuf();
		if (pbuf->open(url, std::ifstream::binary)==NULL){
			exist = false;
			printf(" EXIST FIRST-FALSE %d\n", exist);
		}
		else{
			exist = true;
			printf(" EXIST FIRST-TRUE %d\n", exist);
		}

		//File exist in cache
		if (exist == true){
			// get file size using buffer's members
			std::size_t size = pbuf->pubseekoff(0, ifs.end, ifs.in);
			pbuf->pubseekpos(0, ifs.in);
			// get file data
			pbuf->sgetn(buffer, size);
			ifs.close();
			if (send(sock, buffer,size , 0) < 0){

			}
		}
		//file not in cache
		if (exist == false){
    for (std::map<int, std::string>::iterator it = g_mapwebRecords.begin(); it != g_mapwebRecords.end(); ++it)
    {
       //std::cout << str1 << " => " << it->second.m_dwRecordID << ","<<it->second.m_szFirstName<<","<<it->second.m_szLastName<<","<<it->second.m_szEmailAddress<<","<<it->second.m_wPIN<<","<<it->second.dw_SSN<<","<<it->second.m_dwDDL<<'\n';
		if(it->second==token){
			checkin==true;
		}
    }
	if(checkin==false){
			int sock_send;
			struct sockaddr_in	addr_send;
			int	i, text;
			int	send_len, bytes_sent;
			char  buff[BUF_SIZE];//contain temporary file name request
			//TODO CONNECT TO HTTP 80
			/* create socket for sending data */
			sock_send = socket(AF_INET, SOCK_STREAM, 0);
			if (sock_send < 0) {
				printf("socket() failed\n");
				exit(0);
			}
			/* create socket address structure to connect to */
			memset(&addr_send, 0, sizeof(addr_send)); /* zero out structure */
			addr_send.sin_family = AF_INET; /* address family */
			addr_send.sin_addr.s_addr = htonl(INADDR_ANY);
			addr_send.sin_port = htons((unsigned short)HTTP_PORT);

//			/* connect to the HTTP Socket  */
//			i = connect(sock_send, (struct sockaddr *) &addr_send, sizeof(addr_send));
//			if (i < 0) {
//				printf("connect() failed\n");
//				close(sock_send);
//				exit(0);
//			}
//Check Port number status
	int statu = bind(text, (struct sockaddr *) &addr_send,
		sizeof(addr_send));
	if (statu < 0) {
		perror("bind()text failed");
		close(text);
		exit(1);
	}
	// Listen port number
	statu = listen(text, 5);
	if (statu < 0) {
		perror("listen()text failed");
		close(text);
		exit(1);
	}
			std::string word=weblink;
			word.replace(1,4,"GET http://" );
			word=""+word+" HTTP/1.0\n\n";
			 printf(" WEBLINK THING FIRST %s\n", word.c_str());
			if (send(sock_send, &word,word.length() , 0) < 0){

			}
			 // allocate memory for file content
			std::string response;
			if(recv(sock_send,&response,response.size(), 0)<0){
        //ERROR_CONNECT_RESPONSE
    }
 printf(" WEBLINK THING RESPONSE %s\n", response.c_str());

//			if(write(sock_send,word,sizeof(word))==-1){
//
//			}

			std::streambuf *psbuf1, *backup1;
 	 std::ofstream filestr1(url,std::ofstream::binary);
	 // write to outfile
  //filestr1.write((char *)& response,sizeof(response)) ;
  filestr1<<response;
  filestr1.close();
  	if (send(sock, &response,response.length() , 0) < 0){

			}
  delete &response;
  delete &word;

  // char b[1];
//   int fdA = open(url,O_RDWR);
//    int n_char=0;
   //Use the read system call to obtain fdA one byte at time
  // while (read(fdA, b, 1)!=0)
  //  {
    // n_char=write(fdB,buffer,1);

  //   }


//  	//filestr.open (url);
////backup = std::cout.rdbuf();     // back up cout's streambuf
//	 psbuf1 = filestr1.rdbuf();        // get file's streambuf
//  	std::cout.rdbuf(psbuf1);         // assign streambuf to cout
//////  iterate over the map



			//send a connection request
			//bytes_sent = send(sock_send, buff, BUF_SIZE, 0);
			//if (bytes_sent < 0){

			//}

		//	int fdB = open("/home/knk0055/public_html/text51.txt", O_CREAT | O_RDWR, 0644);

}
if(checkin==true){
buf1="Blocking website :";
buf1.append(token);
if (send(sock,&buf1, buf1.length(), 0) < 0){
				//TODO error  CNP_ACCONT_MESSAGE
        }

		}
	}
	delete &exist;
	delete buffer;
	delete &checkin;
	delete &url;
	//close(sock_send);
	}
close(sock);
//free(sock_desc);
threadCount++;
}
