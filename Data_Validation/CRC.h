#pragma once
class CCRC
{
private:
	class CCRC32
	{
	private:
		ULONG m_crc32_table[256];
		ULONG m_ulPolynomial;

	private:
		/////////////////////////////////////////////////////////////
		// Reflection is a requirement for the official CRC-32 standard.
		// You can create CRCs without it, but they won't conform to the standard.
		//////////////////////////////////////////////////////////////////////////
		ULONG Reflect(ULONG ref, char ch)
		{                                 // Used only by Init_CRC32_Table()

			ULONG value(0);

			// Swap bit 0 for bit 7
			// bit 1 for bit 6, etc.
			for(int i = 1; i < (ch + 1); i++)
			{
				if(ref & 1)
					value |= 1 << (ch - i);
				ref >>= 1;
			}
			return value;
		}

		long getFileSize(FILE* input)
		{
			long fileSizeBytes;
			fseek(input, 0, SEEK_END);
			fileSizeBytes = ftell(input);
			fseek(input, 0, SEEK_SET);

			return fileSizeBytes;
		}
		void InitCrcTable(void)
		{
			// 256 values representing ASCII character codes.
			for(int i = 0; i <= 0xFF; ++i)
			{
				m_crc32_table[i]=Reflect(i, 8) << 24;
				for (int j = 0; j < 8; ++j)
					m_crc32_table[i] = (m_crc32_table[i] << 1) ^ (m_crc32_table[i] & (1 << 31) ? m_ulPolynomial : 0);
				m_crc32_table[i] = Reflect(m_crc32_table[i], 32);
			}
		}

		int Get_CRC(unsigned char* buffer, ULONG bufsize)
		{

			ULONG  crc(0xffffffff);
			int len;
			len = bufsize;
			// Save the text in the buffer.

			// Perform the algorithm on each character
			// in the string, using the lookup table values.

			for(int i = 0; i < len; i++)
				crc = (crc >> 8) ^ m_crc32_table[(crc & 0xFF) ^ buffer[i]];


			// Exclusive OR the result with the beginning value.
			return crc^0xffffffff;

		}

	public : 
		CCRC32()
		{
			m_ulPolynomial = 0x04c11db7;
			for( int i = 0; i < 256; ++i )
			{
				m_crc32_table[i] = 0;
			}
		}


		bool DoCRC( const char* In_strFileName, int& Out_nCRC )
		{

			bool bRet = false;

			do 
			{
				FILE *fs = fopen( In_strFileName, "rb");
				if(fs == NULL)
				{				
					//printf("\nError opening file %s\n", strFileName );
					break;
				}

				long bufsize = getFileSize(fs), result;
				unsigned char *buffer = new unsigned char[bufsize];

				if(buffer == NULL)
				{
					//printf("\nError out of memory\n");
					break;
				}

				// copy the file into the buffer:
				result = fread (buffer,1,bufsize,fs);
				fclose(fs);

				if(result != bufsize) 
				{
					//printf("\nError reading file %s\n", In_strFileName);
					break;
				}

				InitCrcTable(); 
				Out_nCRC = Get_CRC(buffer, bufsize);
				//printf("\nCRC: 0x%X\n",crc);
				delete [] buffer;

				bRet = true;

			} while ( false );


			return bRet;
		}

	};

public:
	CCRC(void);
	~CCRC(void);
	BOOL GetFileCRC32( IN CString In_strPath, OUT int& Out_nCRC );
};

