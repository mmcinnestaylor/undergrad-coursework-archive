class House
{
public:
	House(int size, char border = 'X', char fill = '*'); 
	int GetSize();
	int Perimeter();
	double Area();
	void Grow();
	void Shrink();
	void SetBorder(char border);
	void SetFill(char fill);
	void Draw();
	void Summary();
private:
	int baseSize;
	char houseBorder;
	char houseFill;
};
