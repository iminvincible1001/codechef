 #include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
class FastInput {
public:
    FastInput() {
        m_dataOffset = 0;
        m_dataSize = 0;
        m_v = 0x80000000;
    }
    uint32_t ReadNext() {
        if (m_dataOffset == m_dataSize) {
            int r = read(0, m_buffer, sizeof(m_buffer));
            if (r <= 0) return m_v;
            m_dataOffset = 0;
            m_dataSize = 0;
            int i = 0;
            if (m_buffer[0] < '0') {
                if (m_v != 0x80000000) {
                    m_data[m_dataSize++] = m_v;
                    m_v = 0x80000000;
                }
                for (; (i < r) && (m_buffer[i] < '0'); ++i);
            }
            for (; i < r;) {
                if (m_buffer[i] >= '0') {
                    m_v = m_v * 10 + m_buffer[i] - 48;
                    ++i;
                } else {
                    m_data[m_dataSize++] = m_v;
                    m_v = 0x80000000;
                    for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
                }
            }
        }
        return m_data[m_dataOffset++];
    }
public:
    uint8_t m_buffer[32768];
    uint32_t m_data[16384];
    size_t m_dataOffset, m_dataSize;
    uint32_t m_v;
};
class FastOutput {
public:
    FastOutput() {
        m_dataOffset = 0;
    }
    ~FastOutput() {
    }
    void Flush() {
        if (m_dataOffset) {
            if (write(1, m_data, m_dataOffset));
            m_dataOffset = 0;
        }
    }
    void PrintUint(uint32_t v, char d) {
        if (m_dataOffset + 11 > sizeof(m_data)) Flush();
        if (v < 100000) {
            if (v < 1000) {
                if (v < 10) {
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 1;
                } else if (v < 100) {
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 2;
                } else {
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 3;
                }
            } else {
                if (v < 10000) {
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 4;
                } else {
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 5;
                }
            }
        } else {
            if (v < 100000000) {
                if (v < 1000000) {
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 6;
                } else if (v < 10000000) {
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 7;
                } else {
                    m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 8;
                }
            } else {
                if (v < 1000000000) {
                    m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 9;
                } else {
                    m_data[m_dataOffset + 9] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 8] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 7] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 6] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 5] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 4] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 3] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 2] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 1] = v - v / 10 * 10 + 48;
                    v /= 10;
                    m_data[m_dataOffset + 0] = v + 48;
                    m_dataOffset += 10;
                }
            }
        }
        m_data[m_dataOffset++] = d;
    }
    void PrintChar(char d) {
        if (m_dataOffset + 1 > sizeof(m_data)) Flush();
        m_data[m_dataOffset++] = d;
    }
    void ReplaceChar(int offset, char d) {
        m_data[m_dataOffset + offset] = d;
    }
public:
    uint8_t m_data[32768];
    size_t m_dataOffset;
};

 #define FOR(a,b,i) for(int i=a; i<=b; i++)
 int main(){
	 int t;
	 FastInput fi;
	 t = fi.ReadNext();
	 //cin >> t;
	 while(t--){
		 int ans = 0,n;
		// cin >> n;
		 //vector<string> arr(n);
		// FOR(0,n-1,i) cin >> arr[i];
		 n = fi.ReadNext();
		char arr[n][n];
		FOR(0,n-1,i) FOR(0,n-1,j) arr[i][j] = fi.ReadNext();

		 FOR(0,n-1,r)
		 FOR(0,n-1,c){
			 int f = 0,f1 = 0;
			 int co = 0;
			 FOR(r,n-1,i){
				 if(arr[i][c] == '#'){
					 f = 1;
					 break;
				 }else
					 co++;
			 }
			 FOR(c+1,n-1,j){
				 if(arr[r][j] == '#'){
					 f1= 1;
					 break;
				 }else
					 co++;
			 }

			 if(f1 == 0 && f == 0){
				 ans += 1;
			 }
		 }

		 printf("%d\n",ans);

	 }

 return 0;
 }
