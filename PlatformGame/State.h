#ifndef STATE_H
#define	STATE_H



class State
{
private:
	SDL_Window* mWindow;
	std::vector<SDL_Texture*> mTexture;
	bool mExit;
public:
	State();
	State(SDL_Window* mWindow);
	~State();

	const bool& getExit() const;

	void ExitEvent();


	

	virtual void CheckForExit();

	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	
};

#endif

