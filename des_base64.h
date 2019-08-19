

#ifndef DESH
#define DESH
#include <string>
//c++ 实现des加密算法
//https://www.zhaokeli.com/article/8223.html
using namespace std;
//---------------------------------------------------------------------------  
//////////////////////////////////////////////////////////////////////  
//                                                                  //  
// DES.h: declaration of the TDES、TBase64、TBase64DES class.     //  
//                                                                  //  
//////////////////////////////////////////////////////////////////////  
/* TDES类说明
*
* 该类是DES和3DES算法类
*
*/
class CDES
{
public:
	CDES();
	virtual ~CDES();
	static char* Hex2Bits(string s);
	static string Bits2Hex(char* bytes, int bytelength);
	//des加密蓝天解密,返回值为十六进制字符串
	static string EnCode(string str, string sKey);
	static string DeCode(string str, string sKey);
protected:
	typedef bool(*PSubKey)[16][48];
	//计算并填充子密钥到SubKey数据中  
	static void SetSubKey(PSubKey pSubKey, const unsigned char Key[8]);
	//DES单元运算  
	static void DES(unsigned char Out[8], const unsigned char In[8], const PSubKey pSubKey, bool Type);
	/* 补足8位数据
	*
	* Description    : 根据协议对加密前的数据进行填充
	* @param nType   : 类型：PAD类型
	* @param In      : 数据串指针
	* @param Out     : 填充输出串指针
	* @param datalen : 数据的长度
	* @param padlen  : (in,out)输出buffer的长度，填充后的长度
	* @return true--成功；false--失败；
	*/
	static bool RunPad(bool bType, int nType, const unsigned char* In,
		unsigned datalen, unsigned char* Out, unsigned& padlen);
	/* 执行DES算法对文本加解密
	*
	* Description    : 执行DES算法对文本加解密
	* @param bType   : 类型：加密ENCRYPT，解密DECRYPT
	* @param bMode   : 模式：ECB,CBC
	* @param In      : 待加密串指针
	* @param Out     : 待输出串指针
	* @param datalen : 待加密串的长度，同时Out的缓冲区大小应大于或者等于datalen
	* @param Key     : 密钥(可为8位,16位,24位)支持3密钥
	* @param keylen  : 密钥长度，多出24位部分将被自动裁减
	* @return true--成功；false--失败；
	*/
	static bool RunDES(bool bType, bool bMode, int PaddingMode, const unsigned char* IV, const unsigned char* In,
		unsigned char* Out, unsigned datalen, const unsigned char* Key, unsigned keylen);
private:
	static int hexCharToInt(char c);
	//加密解密  
	enum
	{
		ENCRYPT = 0,    // 加密  
		DECRYPT,        // 解密  
	};
	//DES算法的模式  
	enum
	{
		ECB = 0,    // ECB模式  
		CBC             // CBC模式  
	};
	//Pad填充的模式  
	enum
	{
		PAD_ISO_1 = 0,  // ISO_1填充：数据长度不足8比特的倍数，以0x00补足，如果为8比特的倍数，补8个0x00  
		PAD_ISO_2,      // ISO_2填充：数据长度不足8比特的倍数，以0x80,0x00..补足，如果为8比特的倍数，补0x80,0x00..0x00  
		PAD_PKCS_7      // PKCS7填充：数据长度除8余数为n,以(8-n)补足为8的倍数，如果为8比特的倍数，补8个0x08  
	};
};
//---------------------------------------------------------------------------  
/* TBase64类说明
*
* 该类是Base64编码类
*
*/
class TBase64
{
public:
	static char* Base64_Encode(const char* src);
	static char* Base64_Decode(const char* src);
protected:
	static void Base64_Encode(unsigned char* src, unsigned char* dest, int srclen);
	static void Base64_Decode(unsigned char* src, unsigned char* dest, int srclen);
	static int GetLenEncode(const char* src);
	static int GetLenDecode(const char* src);
};
//---------------------------------------------------------------------------  
#endif
