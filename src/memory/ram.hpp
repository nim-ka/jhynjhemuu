#pragma once

class RDRAM {
	public:
		RDRAM(size_t size);

		template <typename T> void read(word address, T *dest);
		template <typename T> void write(word address, T src);

	private:
		byte *data;
};
