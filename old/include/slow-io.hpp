#pragma once

struct Slow_IO_Singleton {
	Slow_IO_Singleton() {
		ios_base::sync_with_stdio( false );

		std::cin.tie( nullptr );
		std::cout.tie( nullptr );

		setlocale(LC_ALL,"C");

		const int buffer_size = 32768;

		static char stdin_buffer[ buffer_size ];
		static char stdout_buffer[ buffer_size ];

		cin.rdbuf()->pubsetbuf( stdin_buffer, buffer_size );
		cout.rdbuf()->pubsetbuf( stdout_buffer, buffer_size );
	}

	~Slow_IO_Singleton() {

	}
};


Slow_IO_Singleton slow_io_singleton;

