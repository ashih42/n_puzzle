#include "Visualizer.hpp"
#include "VisualizerInitializationException.hpp"
#include "Board.hpp"
#include "MoveLeft.hpp"
#include "MoveRight.hpp"
#include "MoveDown.hpp"
#include "MoveUp.hpp"

const SDL_Color		Visualizer::_WHITE = {255, 255, 255, 255};
const SDL_Color		Visualizer::_RED = {255, 0, 0, 255};
const SDL_Color		Visualizer::_GREEN = {0, 255, 0, 255};

Visualizer::Visualizer( NPuzzle & puzzle ) :
	_puzzle(puzzle), _quit(false), _window(NULL), _renderer(NULL), _font(NULL), _showHint(false), _useBackground(0), _backgroundTexture()
{
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_VIDEO))
		throw VisualizerInitializationException("SDL_Init() failed");
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
		throw VisualizerInitializationException("IMG_Init() failed");
	if (TTF_Init())
		throw VisualizerInitializationException("TTF_Init() failed");
	
	char * basePath = SDL_GetBasePath();

	if (basePath)
	{
		this->_path = basePath;
		SDL_free(basePath);
	}
	else
		throw VisualizerInitializationException("SDL_GetBasePath() failed");

	int windowWidth = this->_puzzle._board.getSize() * PIECE_WIDTH;

	if (!(this->_window = SDL_CreateWindow("NPuzzle", 100, 100, windowWidth, windowWidth, SDL_WINDOW_SHOWN)))
		throw VisualizerInitializationException("SDL_CreateWindow() failed");
	if (!(this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw VisualizerInitializationException("SDL_CreateRenderer() failed");
	if (!(this->_font = TTF_OpenFont((this->_path + FONT_FILE).c_str(), FONT_SIZE)))
		throw VisualizerInitializationException("TTF_OpenFont() failed");

	if (!(this->_backgroundTexture[0] = IMG_LoadTexture(this->_renderer, (this->_path + BG_PIC_00).c_str())) ||
		!(this->_backgroundTexture[1] = IMG_LoadTexture(this->_renderer, (this->_path + BG_PIC_01).c_str())) ||
		!(this->_backgroundTexture[2] = IMG_LoadTexture(this->_renderer, (this->_path + BG_PIC_02).c_str())) ||
		!(this->_backgroundTexture[3] = IMG_LoadTexture(this->_renderer, (this->_path + BG_PIC_03).c_str())) ||
		!(this->_backgroundTexture[4] = IMG_LoadTexture(this->_renderer, (this->_path + BG_PIC_04).c_str())) ||
		!(this->_backgroundTexture[5] = IMG_LoadTexture(this->_renderer, (this->_path + BG_PIC_05).c_str())))
		throw VisualizerInitializationException("IMG_LoadTexture() failed");

	this->_render();
}

Visualizer::~Visualizer( void )
{
	TTF_CloseFont(this->_font);
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
	for (int i = 0; i < BACKGROUND_COUNT; i++)
		SDL_DestroyTexture(this->_backgroundTexture[i]);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void				Visualizer::loop( void )
{
	while (!this->_quit)
	{
		this->_handleEvents();
	}
}

void				Visualizer::_handleEvents( void )
{
	SDL_Event		e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->_quit = true;
		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					this->_quit = true;
					return;
				case SDLK_TAB:
					this->_useBackground = (this->_useBackground + 1) % (BACKGROUND_COUNT + 1);
					break;
				case SDLK_LEFT:
					if (this->_puzzle._board.isSolved()) return;
					this->_puzzle._processMove(new MoveLeft());
					break;
				case SDLK_RIGHT:
					if (this->_puzzle._board.isSolved()) return;
					this->_puzzle._processMove(new MoveRight());
					break;
				case SDLK_DOWN:
					if (this->_puzzle._board.isSolved()) return;
					this->_puzzle._processMove(new MoveDown());
					break;
				case SDLK_UP:
					if (this->_puzzle._board.isSolved()) return;
					this->_puzzle._processMove(new MoveUp());
					break;
				case SDLK_BACKSPACE:
					this->_puzzle._undoLastMove();
					break;
				case SDLK_r:
					this->_puzzle._reset();
					break;
				case SDLK_h:
					this->_showHint = !this->_showHint;
					break;
				case SDLK_p:
					this->_puzzle._printMoves();
					break;
				case SDLK_s:
					this->_puzzle._reset();
					this->_render();
					this->_puzzle._solve(*this);
					break;
				case SDLK_d:
					this->_puzzle._board.debug();
					break;
				case SDLK_m:
					this->_puzzle._switchSearchMethod();
					break;
				case SDLK_k:
					this->_puzzle._switchHeuristic();
					break;
				default:
					return;
			}
			this->_render();
		}
	}
}

void				Visualizer::_render( void )
{
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->_renderer);

	for (int y = 0; y < this->_puzzle._board.getSize(); y++)
		for (int x = 0; x < this->_puzzle._board.getSize(); x++)
			this->_drawPiece(x, y);

	SDL_RenderPresent(this->_renderer);

	std::string windowTitle = "Moves: " + std::to_string(this->_puzzle._moveStack.size());
	SDL_SetWindowTitle(this->_window, windowTitle.c_str());
}

void				Visualizer::_drawPiece( int x, int y )
{
	Piece &			piece = this->_puzzle._board.getPiece(x, y);
	
	if (piece.getValue() == 0) return;

	int posX = x * PIECE_WIDTH;
	int posY = y * PIECE_WIDTH;
	SDL_Rect boxRect = {posX, posY, PIECE_WIDTH - 1, PIECE_WIDTH - 1};
	
	if (this->_useBackground)
	{
		SDL_Texture * tex = this->_backgroundTexture[this->_useBackground - 1];
		int w, h;
		SDL_QueryTexture(tex, NULL, NULL, &w, &h);
		int srcWidth = w / this->_puzzle._board.getSize();
		int srcHeight = h / this->_puzzle._board.getSize();

		int srcPosX = (piece.getValue() - 1) % this->_puzzle._board.getSize() * srcWidth;
		int srcPosY = (piece.getValue() - 1) / this->_puzzle._board.getSize() * srcHeight;

		SDL_Rect srcRect = { srcPosX, srcPosY, srcWidth, srcHeight };
		SDL_Rect dstRect = { posX, posY, PIECE_WIDTH, PIECE_WIDTH};

		SDL_RenderCopy(this->_renderer, tex, &srcRect, &dstRect);
	}
	else
	{
		this->_drawText(piece.toString(), boxRect, Visualizer::_WHITE);
		this->_drawRect(boxRect, Visualizer::_WHITE);
	}

	if (this->_showHint)
		this->_drawRect(boxRect, piece.isAtCorrectPos() ? Visualizer::_GREEN : Visualizer::_RED);
}

void				Visualizer::_drawRect(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(this->_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(this->_renderer, rect.x, rect.y, rect.x + rect.w, rect.y);
	SDL_RenderDrawLine(this->_renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h);
	SDL_RenderDrawLine(this->_renderer, rect.x, rect.y, rect.x, rect.y + rect.h);
	SDL_RenderDrawLine(this->_renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h);
}

void				Visualizer::_drawText(const std::string & message, SDL_Rect rect, SDL_Color color)
{
	SDL_Surface *	surface;
	SDL_Texture *	texture;
	SDL_Rect		textRect;

	if (!(surface = TTF_RenderText_Blended(this->_font, message.c_str(), color)))
		return;
	if (!(texture = SDL_CreateTextureFromSurface(this->_renderer, surface)))
	{
		SDL_FreeSurface(surface);
		return;
	}

	textRect = rect;
	if (message.length() == 3)
		textRect.x += 3;
	else if (message.length() == 2)
		textRect.x += 11;
	else
		textRect.x += 18;
	textRect.y += 12;

	SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(this->_renderer, texture, NULL, &textRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
