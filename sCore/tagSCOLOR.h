typedef struct tagSCOLOR
{
	//���캯��
	tagSCOLOR();
	tagSCOLOR(unsigned long dwColor);
	tagSCOLOR(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue);
	tagSCOLOR(unsigned char red, unsigned char green, unsigned char blue);

	//������ɫ�ķ���
	void SetAlpha(unsigned char alpha);
	void SetRed(unsigned char red);
	void SetGreen(unsigned char green);
	void SetBlue(unsigned char blue);

	//ȡ����ɫ�ķ���
	unsigned char GetAlpha();
	unsigned char GetRed();
	unsigned char GetGreen();
	unsigned char GetBlue();

	//������ɫ
	unsigned long GetColor();
	void SetColor(unsigned long dwColor);

	tagSCOLOR &operator =(unsigned long dwColor);
	tagSCOLOR &operator =(const tagSCOLOR sColor);

	unsigned long dwColor = 0x00;				//32λ4�ֽ�,64λ8�ֽ�
}SCOLOR;