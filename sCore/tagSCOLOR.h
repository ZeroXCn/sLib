typedef struct tagSCOLOR
{
	//构造函数
	tagSCOLOR();
	tagSCOLOR(unsigned long dwColor);
	tagSCOLOR(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue);
	tagSCOLOR(unsigned char red, unsigned char green, unsigned char blue);

	//设置颜色的分量
	void SetAlpha(unsigned char alpha);
	void SetRed(unsigned char red);
	void SetGreen(unsigned char green);
	void SetBlue(unsigned char blue);

	//取得颜色的分量
	unsigned char GetAlpha();
	unsigned char GetRed();
	unsigned char GetGreen();
	unsigned char GetBlue();

	//设置颜色
	unsigned long GetColor();
	void SetColor(unsigned long dwColor);

	tagSCOLOR &operator =(unsigned long dwColor);
	tagSCOLOR &operator =(const tagSCOLOR sColor);

	unsigned long dwColor = 0x00;				//32位4字节,64位8字节
}SCOLOR;