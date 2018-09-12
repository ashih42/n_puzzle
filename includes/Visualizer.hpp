#ifndef VISUALIZER_HPP
# define VISUALIZER_HPP

# include <string>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include "NPuzzle.hpp"

# define PIECE_WIDTH		50

# define BACKGROUND_COUNT	6
# define BG_PIC_00			"images/doge_rainbow.jpg"
# define BG_PIC_01			"images/tty.png"
# define BG_PIC_02			"images/mstumpy2.png"
# define BG_PIC_03			"images/u_w0t_m8.jpg"
# define BG_PIC_04			"images/hammer.jpg"
# define BG_PIC_05			"images/sunset.png"

# define FONT_FILE			"fonts/sample_font.ttf"
# define FONT_SIZE			30

class Board;

class Visualizer
{
public:

	Visualizer( NPuzzle & puzzle );
	~Visualizer( void );

	void					loop( void );

private:

	friend class Solver;

	static const SDL_Color	_WHITE;
	static const SDL_Color	_RED;
	static const SDL_Color	_GREEN;

	NPuzzle &				_puzzle;

	bool					_quit;
	std::string				_path;
	SDL_Window *			_window;
	SDL_Renderer *			_renderer;
	TTF_Font *				_font;

	bool					_showHint;
	int						_useBackground;
	SDL_Texture *			_backgroundTexture[BACKGROUND_COUNT];

	Visualizer( void );
	Visualizer( Visualizer const & src );
	Visualizer & operator=( Visualizer const & rhs );

	void					_handleEvents( void );
	void					_render( void );

	void					_drawPiece( int x, int y );
	void					_drawRect(SDL_Rect rect, SDL_Color color);
	void					_drawText(const std::string & message, SDL_Rect rect, SDL_Color color);

};

#endif
