struct Ghost
{
private:

public:
	bool edible; //mangeable quand on passe sur une super pac gomme
	int edible_max_time; //temps d'effet de la super pac gomme
	int edible_timer;
	bool eaten; //fantôme mangé
	bool transporting;
	float color[3];
	double speed;
	double max_speed;
	bool in_jail;
	int jail_timer;
	double angle;
	double x, y;

	Ghost(double, double);


	~Ghost(void);

	void Move(); 
	void Update(void);
	void Chase(double, double, bool*);
	bool Catch(double, double); //collision
	void Reinit(void);
	void Vulnerable(void);
	void Draw(void);
	void game_over(void);
};