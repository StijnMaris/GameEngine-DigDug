#pragma once

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};

	public:
		static bool m_DoContinue;
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	};
}