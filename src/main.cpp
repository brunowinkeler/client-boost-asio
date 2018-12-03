#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main() 
{
	boost::asio::io_service io_service;
	tcp::socket socket(io_service);
	bool is_connected = false;

	try
	{
		socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
		is_connected = true;
	}
	catch (...)
	{
		cout << "It was not possible to connect to server.\n";
	}

	if (is_connected)
	{
		const string msg = "Hello from Client!\n";
		boost::system::error_code error;
		boost::asio::write(socket, boost::asio::buffer(msg), error);

		if (!error) {
			cout << "Client sent hello message!" << endl;
		}
		else {
			cout << "send failed: " << error.message() << endl;
		}
	}

	// This part of code is to receive some data from server.
	// In this example, this funcionality is not necessary.

	//boost::asio::streambuf receive_buffer;
	//boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

	//if( error && error != boost::asio::error::eof ) {
	//  cout << "receive failed: " << error.message() << endl;
	//}
	//else {
	//  const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
	//  cout << data << endl;
	//}

	getchar();
	return 0;
}
