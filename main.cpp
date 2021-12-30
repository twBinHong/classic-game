#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <stdlib.h>

int main() {
	// load sound effect
	sf::SoundBuffer Erase_Buffer;
	if (!Erase_Buffer.loadFromFile("erase.wav")) {
		std::cout << "Erase_Buffer fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Sound Erase_Sound;
	Erase_Sound.setBuffer(Erase_Buffer);

	sf::SoundBuffer Moving_Buffer;
	if (!Moving_Buffer.loadFromFile("moving.wav")) {
		std::cout << "Moving_Buffer fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Sound Moving_Sound;
	Moving_Sound.setBuffer(Moving_Buffer);

	sf::SoundBuffer Rotate_Buffer;
	if (!Rotate_Buffer.loadFromFile("rotate.wav")){
		std::cout << "Rotate_Buffer fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Sound Rotate_Sound;
	Rotate_Sound.setBuffer(Rotate_Buffer);

	sf::SoundBuffer Touch_Down_Buffer;
	if (!Touch_Down_Buffer.loadFromFile("PieceTouchDown.ogg")) {
		std::cout << "Touch_Down_Buffer fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Sound Touch_Down_Sound;
	Touch_Down_Sound.setBuffer(Touch_Down_Buffer);
	
	//	load Texture
	sf::Texture Background_Texture;						// for background
	if (!Background_Texture.loadFromFile("background.png")) {
		std::cout << "Background_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture Yellow_Texture;							// for type O
	if (!Yellow_Texture.loadFromFile("yellow.png")) {
		std::cout << "Yellow_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture LightBlue_Texture;						// for type I
	if (!LightBlue_Texture.loadFromFile("light_blue.png")) {
		std::cout << "LightBlue_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture Green_Texture;							// for tpye L
	if (!Green_Texture.loadFromFile("green.png")) {
		std::cout << "Green_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture Red_Texture;							// for tpye Z
	if (!Red_Texture.loadFromFile("red.png")) {
		std::cout << "Red_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture Blue_Texture;							// for type T
	if (!Blue_Texture.loadFromFile("blue.png")) {
		std::cout << "Blue_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture Purple_Texture;							// for type rZ
	if (!Purple_Texture.loadFromFile("purple.png")) {
		std::cout << "Purple_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Texture Orange_Texture;							// for type rL
	if (!Orange_Texture.loadFromFile("orange.png")) {
		std::cout << "Orange_Texture fail" << std::endl;
		return EXIT_FAILURE;
	}
	// define Type in Tetris
	enum class Type {
		None,
		O,
		I,
		L,
		Z,
		T,
		rZ,
		rL
	};

	std::map<Type, std::vector<std::vector<sf::Vector2i>>> Shapes = {
		{
			Type::O,
			{
				{
					sf::Vector2i(0,  0),
					sf::Vector2i(0, -1),
					sf::Vector2i(1,  0),
					sf::Vector2i(1, -1)
				}
			}
		},
		{
			Type::I,
			{
				{	// horizontal 
					sf::Vector2i(-1, 0),
					sf::Vector2i( 0, 0),
					sf::Vector2i( 1, 0),
					sf::Vector2i( 2, 0)
				},
				{	// vertical
					sf::Vector2i( 0, -2),
					sf::Vector2i( 0, -1),
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0,  1)
				}
			}
		},
		{
			Type::L,
			{
				{	// original
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0, -1),
					sf::Vector2i( 0, -2),
					sf::Vector2i( 1,  0)
				},
				{	// left turn
					sf::Vector2i( 0,  0),
					sf::Vector2i(-1,  0),
					sf::Vector2i(-2,  0),
					sf::Vector2i( 0 ,-1)
				},
				{	// up-side down
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0,  1),
					sf::Vector2i( 0,  2),
					sf::Vector2i(-1,  0)
				},
				{	// reversed
					sf::Vector2i( 0,  0),
					sf::Vector2i( 1,  0),
					sf::Vector2i( 2,  0),
					sf::Vector2i( 0,  1)
				}
			}
		},
		{
			Type::Z,
			{
				{	// original
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0, -1),
					sf::Vector2i(-1, -1),
					sf::Vector2i( 1,  0)
				},
				{	// reversed
					sf::Vector2i( 0,  0),
					sf::Vector2i(-1,  0),
					sf::Vector2i(-1,  1),
					sf::Vector2i( 0, -1)
				}
			}
		},
		{
			Type::T,
			{
				{	// original
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0,  1),
					sf::Vector2i(-1,  0),
					sf::Vector2i( 1,  0)
				},
				{	// left turn
					sf::Vector2i( 0,  0),
					sf::Vector2i(-1,  0),
					sf::Vector2i( 0,  1),
					sf::Vector2i( 0, -1)
				},
				{	// up-side down
					sf::Vector2i( 0,  0),
					sf::Vector2i(-1,  0),
					sf::Vector2i( 1,  0),
					sf::Vector2i( 0, -1)
				},
				{	// right turn
					sf::Vector2i( 0,  0),
					sf::Vector2i( 1,  0),
					sf::Vector2i( 0,  1),
					sf::Vector2i( 0, -1)
				}
			}
		},
		{
			Type::rZ,
			{
				{	//original
					sf::Vector2i( 0,  0),
					sf::Vector2i(-1,  0),
					sf::Vector2i( 0, -1),
					sf::Vector2i( 1, -1)
				},
				{	//reversed
					sf::Vector2i( 0,  0),
					sf::Vector2i( 1,  0),
					sf::Vector2i( 0, -1),
					sf::Vector2i( 1,  1)
				}
			}
		},
		{
			Type::rL,
			{
				{	//original
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0,  1),
					sf::Vector2i( 0,  2),
					sf::Vector2i( 1,  0)
				},
				{	//left turn
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0,  1),
					sf::Vector2i(-1,  0),
					sf::Vector2i(-2,  0)
				},
				{	//up-side down
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0, -1),
					sf::Vector2i( 0, -2),
					sf::Vector2i(-1,  0)
				},
				{	// right turn
					sf::Vector2i( 0,  0),
					sf::Vector2i( 0, -1),
					sf::Vector2i( 1,  0),
					sf::Vector2i( 2,  0)
				}
			}
		}
	};
	//  each type with different color
	std::map<Type, sf::Sprite> Sprites = {
		{Type::O, sf::Sprite(Yellow_Texture)},
		{Type::I, sf::Sprite(LightBlue_Texture)},
		{Type::L, sf::Sprite(Green_Texture)},
		{Type::Z, sf::Sprite(Red_Texture)},
		{Type::T, sf::Sprite(Blue_Texture)},
		{Type::rZ, sf::Sprite(Purple_Texture)},
		{Type::rL, sf::Sprite(Orange_Texture)}
	};
	
	// set initial envirnment
	const int Field_Width = 10;
	const int Field_Height = 20;
	Type field[Field_Width][Field_Height] = {};
	const int Block_Width = Yellow_Texture.getSize().x;
	const int Block_Height = Yellow_Texture.getSize().y;
	const int Window_Width = Field_Width * Block_Width + 220;  // 220 = Block_Width*5.5
	const int Window_Height = Field_Height * Block_Height;
	const float Game_Width = (float)(Field_Width * Block_Width);
	const float Game_Height = (float)(Field_Height * Block_Height);

	sf::RenderWindow window(sf::VideoMode(Window_Width, Window_Height), L"Tetris «XÃ¹´µ¤è¶ô");
	Background_Texture.setRepeated(true);
	sf::Sprite Background_Sprite(Background_Texture,
		sf::IntRect(0, 0, (int)Game_Width, (int)Game_Height));

	// set instruction in the right side 
	sf::RectangleShape Blue_Frame;
	Blue_Frame.setSize(sf::Vector2f((float)(Block_Width * 5), Game_Height -20));
	Blue_Frame.setFillColor(sf::Color::Transparent);
	Blue_Frame.setOutlineColor(sf::Color::Blue);
	Blue_Frame.setOutlineThickness(3);
	Blue_Frame.setPosition(Game_Width + 10, 10);
	//declare and load a font
	sf::Font Font_for_instruction;
	if(!Font_for_instruction.loadFromFile("arial.ttf")) {
			std::cout << "Font_for_instruction fail." << std::endl;
			return EXIT_FAILURE;
	}
	//creat texts
	sf::Text Text_Score(L"Score:", Font_for_instruction);
	Text_Score.setCharacterSize(35);
	Text_Score.setStyle(sf::Text::Bold);
	Text_Score.setPosition(Game_Width + 20, 25);
	// socre number text
	int Score_number = 0;
	sf::String Score_Number(std::to_string(Score_number));
	if (Score_Number.getSize() < 6) {
		while(Score_Number.getSize() < 6) {
			Score_Number.insert(0, "0");
		}
	}
	sf::Text Score_Number_Text(Score_Number, Font_for_instruction);
	Score_Number_Text.setCharacterSize(40);
	Score_Number_Text.setStyle(sf::Text::Bold);
	Score_Number_Text.setPosition(Game_Width + 60, 65);
	// set Next text 
	sf::Text Next_Text(L"NEXT:", Font_for_instruction);
	Next_Text.setCharacterSize(35);
	Next_Text.setStyle(sf::Text::Bold);
	Next_Text.setPosition(Game_Width + 20, 120);

	// set direction text - Rotate
	sf::Text Arrow_Key_Text(L"Arrow Key: ", Font_for_instruction);
	Arrow_Key_Text.setCharacterSize(25);
	Arrow_Key_Text.setStyle(sf::Text::Bold);
	Arrow_Key_Text.setPosition(Game_Width + 20, 420);

	sf::Text Rotat_Text(L"UP: Rotate", Font_for_instruction);
	Rotat_Text.setCharacterSize(20);
	Rotat_Text.setStyle(sf::Text::Bold);
	Rotat_Text.setPosition(Game_Width + 20, 460);
	// set direction text - hard drop
	sf::Text Hard_Drop_Text(L"Down: Hard Drop", Font_for_instruction);
	Hard_Drop_Text.setCharacterSize(20);
	Hard_Drop_Text.setStyle(sf::Text::Bold);
	Hard_Drop_Text.setPosition(Game_Width + 20, 490);
	// set direction text - move left
	sf::Text Move_Left_Text(L"Left: Move Left", Font_for_instruction);
	Move_Left_Text.setCharacterSize(20);
	Move_Left_Text.setStyle(sf::Text::Bold);
	Move_Left_Text.setPosition(Game_Width + 20, 520);
	// set directtion text - move right
	sf::Text Move_Right_Text(L"Right: Move Right", Font_for_instruction);
	Move_Right_Text.setCharacterSize(20);
	Move_Right_Text.setStyle(sf::Text::Bold);
	Move_Right_Text.setPosition(Game_Width + 20, 550);

	// set graph of Arrow key 
	float Key_Pos_Offset_X = Game_Width + 85;
	float Key_Pos_Offset_Y = 630;
	sf::RectangleShape Up_Rectangle;
	Up_Rectangle.setSize(sf::Vector2f(50, 50));
	Up_Rectangle.setFillColor(sf::Color::Transparent);
	Up_Rectangle.setOutlineColor(sf::Color::White);
	Up_Rectangle.setOutlineThickness(4);
	Up_Rectangle.setPosition(Key_Pos_Offset_X, Key_Pos_Offset_Y);

	sf::CircleShape Up_Triangle(15.f, 3);
	Up_Triangle.setFillColor(sf::Color::Transparent);
	Up_Triangle.setOutlineColor(sf::Color::White);
	Up_Triangle.setOutlineThickness(3);
	Up_Triangle.setPosition(Key_Pos_Offset_X + 10, Key_Pos_Offset_Y + 13);

	sf::RectangleShape Down_Rectangle;
	Down_Rectangle.setSize(sf::Vector2f(50, 50));
	Down_Rectangle.setFillColor(sf::Color::Transparent);
	Down_Rectangle.setOutlineColor(sf::Color::White);
	Down_Rectangle.setOutlineThickness(4);
	Down_Rectangle.setPosition(Key_Pos_Offset_X, Key_Pos_Offset_Y + 70);

	sf::CircleShape Down_Triangle(15.f, 3);
	Down_Triangle.setFillColor(sf::Color::Transparent);
	Down_Triangle.setOutlineColor(sf::Color::White);
	Down_Triangle.setOutlineThickness(3);
	Down_Triangle.setPosition(Key_Pos_Offset_X + 40, Key_Pos_Offset_Y + 107);
	Down_Triangle.setRotation(180);

	sf::RectangleShape Left_Rectangle;
	Left_Rectangle.setSize(sf::Vector2f(50, 50));
	Left_Rectangle.setFillColor(sf::Color::Transparent);
	Left_Rectangle.setOutlineColor(sf::Color::White);
	Left_Rectangle.setOutlineThickness(4);
	Left_Rectangle.setPosition(Key_Pos_Offset_X - 65, Key_Pos_Offset_Y + 70);

	sf::CircleShape Left_Triangle(15.f, 3);
	Left_Triangle.setFillColor(sf::Color::Transparent);
	Left_Triangle.setOutlineColor(sf::Color::White);
	Left_Triangle.setOutlineThickness(3);
	Left_Triangle.setPosition(Key_Pos_Offset_X - 50, Key_Pos_Offset_Y + 110);
	Left_Triangle.setRotation(270);

	sf::RectangleShape Right_Rectangle;
	Right_Rectangle.setSize(sf::Vector2f(50, 50));
	Right_Rectangle.setFillColor(sf::Color::Transparent);
	Right_Rectangle.setOutlineColor(sf::Color::White);
	Right_Rectangle.setOutlineThickness(4);
	Right_Rectangle.setPosition(Key_Pos_Offset_X + 65, Key_Pos_Offset_Y + 70);

	sf::CircleShape Right_Triangle(15.f, 3);
	Right_Triangle.setFillColor(sf::Color::Transparent);
	Right_Triangle.setOutlineColor(sf::Color::White);
	Right_Triangle.setOutlineThickness(3);
	Right_Triangle.setPosition(Key_Pos_Offset_X + 103, Key_Pos_Offset_Y + 80);
	Right_Triangle.setRotation(90);

	// set Game over text
	sf::Text Game_Over_Text(L"Game Over", Font_for_instruction);
	Game_Over_Text.setCharacterSize(65);
	Game_Over_Text.setStyle(sf::Text::Bold);
	//Game_Over_Text.setFillColor(sf::Color::Transparent);
	Game_Over_Text.setOutlineThickness(5);
	Game_Over_Text.setOutlineColor(sf::Color::Red);
	Game_Over_Text.setPosition(Game_Width / 3, Game_Height / 3);

	//set status at the beginning
	srand((unsigned int)time(NULL));
	Type Current_Type = Type(rand() % 7 + 1);
	int Current_Index = 0;
	std::vector<sf::Vector2i> Current_Shape;
	sf::Sprite Current_Sprit;
	std::vector<sf::Vector2i> Coming_Shape;
	sf::Sprite Coming_Sprit;
	Type Coming_Type = Type(rand() % 7 + 1);
	
	// define square position
	const sf::Vector2i Origin_position(Field_Width/2, 0);
	sf::Vector2i Pos(Origin_position);

	bool isDead = false;
	sf::Clock Clock;
	while (window.isOpen()) {
		
		Current_Shape = Shapes[Current_Type][Current_Index];
		Current_Sprit = Sprites[Current_Type];
		Coming_Shape = Shapes[Coming_Type][0];
		Coming_Sprit = Sprites[Coming_Type];

		enum class Action {
			Hold,
			Move_Down,
			Move_Left,
			Move_Right,
			Move_Rotate,
			Hard_Drop
		};
		Action Act = Action::Hold;

		if (Clock.getElapsedTime().asSeconds() >= 0.55f) {
			Act = Action::Move_Down;
			if (isDead == false) {
				Moving_Sound.play();
			}
			Clock.restart();
		}
		//detect event
		sf::Event Evt;
		if (window.pollEvent(Evt)) {
			if (Evt.type == sf::Event::Closed) {
				window.close();
			}
			if (Evt.type == sf::Event::KeyPressed && isDead == false) {
				switch (Evt.key.code) {
					case sf::Keyboard::Left:
						Act = Action::Move_Left;
						Left_Rectangle.setFillColor(sf::Color::Red);
						break;
					case sf::Keyboard::Right:
						Act = Action::Move_Right;
						Right_Rectangle.setFillColor(sf::Color::Red);
						break;
					case sf::Keyboard::Up:
						Act = Action::Move_Rotate;
						Up_Rectangle.setFillColor(sf::Color::Red);
						break;
					case sf::Keyboard::Down:
						Act = Action::Hard_Drop;
						Down_Rectangle.setFillColor(sf::Color::Red);
						break;
				}
			}
			else {
				Left_Rectangle.setFillColor(sf::Color::Transparent);
				Up_Rectangle.setFillColor(sf::Color::Transparent);
				Down_Rectangle.setFillColor(sf::Color::Transparent);
				Right_Rectangle.setFillColor(sf::Color::Transparent);
			}
		}

		
		sf::Vector2i Next_Pos(Pos);
			
		// recognize rotation
		int Next_Index = Current_Index;
		if (Act == Action::Move_Rotate && isDead == false) {
			//check what kind of direction the square has
			Next_Index = (Next_Index + 1) % Shapes[Current_Type].size();
			if (Shapes[Current_Type].size() > 1 ) {
				Rotate_Sound.play();
			}
		}
		std::vector<sf::Vector2i> Next_Shape = Shapes[Current_Type][Next_Index];

		if (!isDead) {
			switch (Act) {
				case Action::Hold:
					break;
				case Action::Move_Down:
					Next_Pos.y++;
					break;
				case Action::Move_Left:
					Next_Pos.x--;
					break;
				case Action::Move_Right:
					Next_Pos.x++;
					break;
				case Action::Hard_Drop:
					bool isEmpty = true;
					while (isEmpty) {
						Next_Pos.y++;
						for (const sf::Vector2i& d : Next_Shape) {
							sf::Vector2i Check_NP = Next_Pos + d;
							if (Check_NP.y < Field_Height &&
								(Check_NP.y < 0 || field[Check_NP.x][Check_NP.y] == Type::None)) {
								continue;
							}
							else {
								isEmpty = false;
								Next_Pos.y--;
							}
						}
					}
					break;
			}
		}
		//check if next postion is availble
		int Count_Empty = 0;
		for (const sf::Vector2i& d : Next_Shape) {
			sf::Vector2i Check_NP = Next_Pos + d;
			if (Check_NP.x >= 0 && Check_NP.x < Field_Width &&
				Check_NP.y < Field_Height &&
				(Check_NP.y < 0 || field[Check_NP.x][Check_NP.y] == Type::None)) {
				Count_Empty++;
			}
		}
		if (Count_Empty == 4) {
			Pos = Next_Pos;
			Current_Index = Next_Index;
			Current_Shape = Next_Shape; 
		}
		else {	//if the square fall on buttom
			if (Act == Action::Move_Down && isDead == false) {
				for (const sf::Vector2i& d : Current_Shape) {
					sf::Vector2i NP = Pos + d;
					if (NP.y >= 0) {
						field[NP.x][NP.y] = Current_Type;
					}
					// check if game is availble
					if (field[NP.x][0] != Type::None) {
						isDead = true;
					}
				}
				Touch_Down_Sound.play();

				// check if the row is full
				for (int y = 0; y < Field_Height; y++) {
					bool isFull = true;
					for (int x = 0; x < Field_Width; x++) {
						if (field[x][y] == Type::None) {
							isFull = false;
						}
					}
					if (isFull == true) {
						for (int ty = y; ty > 0; ty--) {
							for (int x = 0; x < Field_Width; x++) {
								field[x][ty] = field[x][ty - 1];
							}
						}
						Score_number += 100;

						for (int x = 0; x < Field_Width; x++) {
							field[x][0] = Type::None;
						}
						Erase_Sound.play();
						Score_Number = std::to_string(Score_number);
						if (Score_Number.getSize() < 6) {
							while (Score_Number.getSize() < 6) {
								Score_Number.insert(0, "0");
							}
							Score_Number_Text.setString(Score_Number);
						}
					}
				}

				Pos = Origin_position;
				if (isDead == false) {
					Current_Type = Coming_Type;
					Current_Index = 0;
					Coming_Type = Type(rand() % 7 + 1);
				}
				
			}
		}
		window.clear();
		window.draw(Background_Sprite);
		// draw current status in the field
		for (int x = 0; x < Field_Width; x++) {
			for (int y = 0; y < Field_Height; y++) {
				if (field[x][y] == Type::None)
					continue;
				sf::Sprite& s = Sprites[field[x][y]];
				s.setPosition(
					float(x* Block_Width),
					float(y* Block_Height));
				window.draw(s);
			}
		}
		// draw dropping Shape  
		for (const sf::Vector2i& d : Current_Shape) {
			sf::Vector2i NP = Pos + d;
			Current_Sprit.setPosition(
				float(NP.x * Block_Width),
				float(NP.y * Block_Height));
			window.draw(Current_Sprit);
		}
		// draw right-side instruction
		window.draw(Blue_Frame);
		window.draw(Text_Score);
		window.draw(Score_Number_Text);
		window.draw(Next_Text);
		window.draw(Arrow_Key_Text);
		window.draw(Rotat_Text);
		window.draw(Hard_Drop_Text);
		window.draw(Move_Left_Text);
		window.draw(Move_Right_Text);
		window.draw(Up_Rectangle);
		window.draw(Up_Triangle);
		window.draw(Down_Rectangle);
		window.draw(Down_Triangle);
		window.draw(Left_Rectangle);
		window.draw(Left_Triangle);
		window.draw(Right_Rectangle);
		window.draw(Right_Triangle);
		//draw next shape in the right-side instruction
		for (const sf::Vector2i& d : Coming_Shape) {
			float Offset_Pos_X = Game_Width + (float)Block_Width * 1.8 + (float)d.x * (float)Block_Width;
			float Offset_Pos_Y = Game_Height / 3 + d.y * Block_Height;
			if (Coming_Type == Type::rZ ||
				Coming_Type == Type::Z || Coming_Type == Type::T) {
				Offset_Pos_X += (float)(0.5 * Block_Width);
			}
			if (Coming_Type == Type::rL) {
				Offset_Pos_Y -= 40;
			}
			Coming_Sprit.setPosition(Offset_Pos_X, Offset_Pos_Y);
			window.draw(Coming_Sprit);
		}

		if (isDead) {
			window.draw(Game_Over_Text);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}