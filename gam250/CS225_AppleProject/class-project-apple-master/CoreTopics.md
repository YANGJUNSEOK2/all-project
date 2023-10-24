# CoreTopics
## Course Info
Team Name & Member Name : Apple & Junseok Yang, Seungguk Jang </br>
Project Name : AppleTeam </br>
Course Name : CS225 </br>
Term : Summer 2021</br>
## Introduce Topics
[x] C++ Core Guidelines on Pointers</br>
[x] Variadic Templates</br>
[x] Type Traits</br>
[x] Algorithm Selection</br>
[x] SFINAE - Substitution Failure Is Not An Error</br>
[x] Code Optimization</br>
[x] CPU Caches</br>
[x] Linking - Static Libraries & Shared Libraries</br>
## Explain Topics
### C++ Core Guidelines on Pointers
1 `T*`
2 `owner<T*>`
3 `unique_ptr<T>`
4 `shared_ptr<T>`
5 `span<T>`
6 `dyn_array<T>`
7 `vector<T>`
8 `not_null<T*>`</br>
#### Explaination
Why these are need? </br>
First to first, raw pointer `T*` have no reposible about owner. It is hard to manage resources using raw pointer.</br>
This will make possiblitiy about memory leak or dangling pointer or reference nullptr</br>
Also, User do not know size of array using raw pointer.</br>
So, How can be prevented these?</br>
Having owner make sure to prevent memory leak, resource life time, dangling pointer and reference nullptr and taking length give information about array size</br>
There are 8 types of resource managements. And their relation is the following.</br>
| Type | OwnerShip | Length | Explain |
| ---- | ----- | ------ | ------- |
| `T*` |   No  |   No   | raw pointer, This is good to use for reference |
|`owner<T*>`|   Yes  |   No   | Same with raw pointer except for ownership |
|`unique_ptr<T>`|   Yes  |   No   | This is similar with `owner<T*>` but the key point is that this no need to free the resource explicitly |
|`shared_ptr<T>`|   Yes  |   No   | OwnerShip can be shared by this and no need to mention about free. It is more cost than `unique_ptr<T>` but all of `shared_ptr<T>` that have common ownership free at the same time|
|`span<T>`|   No  |   Yes   | raw pointer except for length |
|`dyn_array<T>`|   Yes  |   Yes   | This also need to free the resource explicitly |
|`vector<T>`|   No  |   Yes   | This seem be same with dyn_array but it no need to free resource explicitly |
|`not_null<T*>`|   No  |   No   | This make sure never the pointer can be nullptr if this take nullptr, compiler give error message |
#### Section to Provide file name and line numbers for all code related requirements.
`T*`, `unique_ptr<T>`, `vector<T>`</br>
SceneManager.h (line : 38-40)
```cpp
std::vector<std::unique_ptr<IScene>> mScenes;
IScene* mCurrentScene;          
IScene* mNextScene;
```
Scenes are not used in other part. It only be used in SceneManager.</br>
So, Scenes just have their ownership itself.</br>
`owner<T*>`
Engine.h (line : 26-31)</br> 
Engine.h (line : 54-61)</br> 
```cpp
    ~Engine() noexcept
    {
        delete inputManager;
        delete window;
        delete sceneManager;
        delete logger;
    }
	...
    gsl::owner<Window*> window = new Window{};
    gsl::owner<SceneManager*> sceneManager = new SceneManager{};
    gsl::owner<InputManager*> inputManager = new InputManager{};
#ifdef _DEBUG
    gsl::owner<Logger*> logger = new Logger(Logger::Severity::DEBUG, true);
#else
    gsl::owner<Logger*> logger = new Logger(Logger::Severity::EVENT, false);
#endif
```
window, sceneManager, inputManager and logger have to take resources until the engine shutdown. </br>
And all of these do not shared own resource.</br>
`not_null<T*>`
Engine.cpp (line : 58-72)
```cpp
bool Engine::InitWindow(gsl::not_null<Window*> pWindow) noexcept
{
    pWindow->Init();
    return true;
}
bool Engine::InitSceneManager(gsl::not_null<SceneManager*> pScene) noexcept
{
    pScene->Load();
    return true;
}
bool Engine::InitInputManager(gsl::not_null<InputManager*> pInput) noexcept
{
    pInput->Init();
    return true;
}
```
window, sceneMAnager, inputManager are essential to the engine so these have to be not nullptr.</br>
`shared_ptr<T>`
Level1.h (line : 22-29, 47)
```cpp
lvImage.loadFromFile(Imgpath::CELL);
lvTexture.loadFromImage(lvImage);
lvSprite = std::make_shared<sf::Sprite>(sf::Sprite{});
lvSprite.get()->setTexture(lvTexture);
lvBoard.SetSprite(lvSprite);
lvBoard.UpdateCellPosition();
mTri.SetSprite(lvSprite);
mTri.UpdateCellPosition();
...
sf::Image lvImage;
sf::Texture lvTexture;
std::shared_ptr<sf::Sprite> lvSprite;
...
```
Board.h (line : 19, 32), Board.cpp(line : 33-37)
```cpp
void SetSprite(std::shared_ptr<sf::Sprite> a_Sprite);
...
std::shared_ptr<sf::Sprite> boardSprite;
```
```cpp
template<int WIDTH, int HEIGHT>
void Board<WIDTH, HEIGHT>::SetSprite(std::shared_ptr<sf::Sprite> a_Sprite)
{
    boardSprite = a_Sprite;
}
```
Triomino.h (line : 28, 39), Triomino.cpp (line : 38-41)
```h
void SetSprite(std::shared_ptr<sf::Sprite> a_Sprite);
...
std::shared_ptr<sf::Sprite> triSprite;
```
```cpp
void Triomino::SetSprite(std::shared_ptr<sf::Sprite> a_Sprite)
{
	triSprite = a_Sprite;
}
```
Cell.h (line : 19), Cell.cpp (line : 13-16)
```h
void SetSprite(std::shared_ptr<sf::Sprite> a_Sprite);
```
```cpp
void Cell::SetSprite(std::shared_ptr<sf::Sprite> aSprite)
{
    cellSprite = *aSprite.get();
}
```
Sprite use same image and texture so we no need to load same image or texture whenever the sprite generate.</br>
So, We make sprite to shared_ptr.
`span<T>`
InputManager.h (line : 18-22, 45)</br>
InputManager.cpp (line : 11-20)</br>
InputManager.cpp (line : 38-44)</br>
```h
~InputManager() noexcept
	{
		waskeyBoard.~span();
		delete[] keyBoard.heap;
	}
	...
static dyn_array keyBoard;
```
```cpp
dyn_array InputManager::keyBoard{ static_cast<int>(InputManager::KeyboardMapping::COUNT) };

void InputManager::Init()
{
    int maxKeyMap = static_cast<int>(keyBoard.size());
    for (int i = 0; i < maxKeyMap; i++)
    {
        keyBoard[i] = false;
    }
}
...
void InputManager::Update() {
    int length = waskeyBoard.size();
    for (int i = 0; i < length; i++)
    {
        waskeyBoard[i] = keyBoard[i];
    }
}
```
`dyn_array<T>`
InputManager.h (line : 18-22, 42)</br>
InputManager.cpp (line 13-20)</br>
```cpp
~InputManager() noexcept
	{
		waskeyBoard.~span();
		delete[] keyBoard.heap;
	}
	...
static dyn_array keyBoard;
```
```cpp
void InputManager::Init() noexcept
{
    int maxKeyMap = static_cast<int>(keyBoard.size());
    for (int i = 0; i < maxKeyMap; i++)
    {
        keyBoard[i] = false;
    }
}
```
### Variadic Templates
#### Explaination
This is one of the template method that can use various type at once.</br>
Variadic template can be used by following example</br>
#### Example
```cpp
int main()
{
    Slash slash;
    Menu menu;
    Level level1;
    Level level2;
    ...
    SceneControl sceneControl;
    sceneControl.AddScene(slash, menu, level1);
    sceneControl.AddScene(level2);
    ...
}
```
```cpp
#include <memory>
class SceneControl
{
template<typename... Args>
    void AddScene(Args... arg)
    {
        mScenes.push_back(arg...));
    }
    ...
};
```
```cpp
[[nodiscard]] constexpr int Sum(int sum)
{
    return sum;
}

template<typename... Args>
[[nodiscard]] constexpr int Sum(int sum, Args... arg) noexcept
{
    return sum + Sum(arg...);
}

int main()
{
    int a = Sum(1,2,3,4,5);
    return 0;
}
```
In the first example, the compiler change the function(void AddScene(Args... arg)) to two function</br>
void AddScene(Splash a_spalsh, Menu a_menu, Level a_level) and void AddScene(Level1 a_level)</br>
So, programer need not make functions that is same except for parameters type.</br>
One more cool thing is that Variadic template no need to take at least one type.</br>
In the second example, when the number of parameter of Sum function is one(no arg...), int Sum(int sum) is called.</br>
In AppleTeam project, these method is used with rvalue. </br>
#### Section to Provide file name and line numbers for all code related requirements.
In AppleTeam, Variadic Template is used in SceneManager. We do not need to make lot of definition of levels and EmplaceScene function.</br>
main.cpp(line : 8,9)</br>
```cpp
int main()
{
    ...
	auto& en = Engine::EngineIns();
	en.SceneManagerIns().EmplaceScene<Splash>();
	en.SceneManagerIns().EmplaceScene<Level1>();
	...
}
```
SceneManager.h(line : 9~13)
```cpp
template<typename Level, typename... Args>
void EmplaceScene(Args&&... arg)
{
    mScenes.push_back(std::make_unique<Level>(std::forward<Args>(arg)...));
}
```
### Type Traits          
### Algorithm Selection  
### SFINAE - Substitution Failure Is Not An Error 
#### Explaination
All of these are integrated. Type Traits is that use instance's type like value but not change like rvalue.</br>
Algorithm Selection is select switch one of structs or function will be used by each user's type.</br>
It can be used any type if the code about type exits.</br>
However, do it need compiler interpret all code although there are code that are not used?</br>
SFINAE make the compiler do not interpret the code which is not used. This cool things make more save time to compile.</br>
#### Section to Provide file name and line numbers for all code related requirements.
`Type Traits`, `Algorithm Selection`, `SFINAE`
Logger.h (line : 29~109)
```cpp

	template< bool B, class T = void >
	using enable_if_t = typename std::enable_if<B, T>::type;

	template<typename T>
	struct is_string : public std::disjunction<std::is_same<const char*, typename std::decay_t<T>>,
		std::is_same<std::string, typename std::decay_t<T>>> {};

	template <typename STRING>
	enable_if_t<is_string<STRING>::value, STRING> LogError(STRING v)
	{
		Log(Severity::ERROR, v);
		return v;
	}
	template <typename STRING>
	typename std::enable_if<is_string<STRING>::value, STRING>::type LogEvent(STRING v)
	{
		Log(Severity::EVENT, v);
		return v;
	}
	template <typename STRING>
	enable_if_t<is_string<STRING>::value, STRING> LogDebug(STRING v)
	{
		Log(Severity::DEBUG, v);
		return v;
	}
	template <typename STRING>
	typename std::enable_if<is_string<STRING>::value, STRING>::type LogVerbose(STRING v)
	{
		Log(Severity::VERBOSE, v);
		return v;
	}

	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type LogError(FLOAT v)
	{
		Log(Severity::ERROR, v);
		return v;
	}
	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type  LogEvent(FLOAT v)
	{
		Log(Severity::EVENT, v);
		return v;
	}
	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type  LogDebug(FLOAT v)
	{
		Log(Severity::DEBUG, v);
		return v;
	}
	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type  LogVerbose(FLOAT v)
	{
		Log(Severity::VERBOSE, v);
		return v;
	}

	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type LogError(INT v)
	{
		Log(Severity::ERROR, v);
		return v;
	}
	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type  LogEvent(INT v)
	{
		Log(Severity::EVENT, v);
		return v;
	}
	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type  LogDebug(INT v)
	{
		Log(Severity::DEBUG, v);
		return v;
	}
	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type  LogVerbose(INT v)
	{
		Log(Severity::VERBOSE, v);
		return v;
	}

```
#### is_string is not default type_traits. We make own that. 
Log() functions are overrided with string, int, float.</br>
The cool thing is that we do not use float version of Log() and then compiler do not assemble that. We can bet that.</br>
### Code Optimization
OPTIMIZE </br>
 In computers, optimization means transforming the system to increase efficiency. and Efficiency means that less time.</br>
 There are many method about increase efficiency. Changing operators(multiply to plus or minus and divide to multiply), less read or write from/to memory, use functional unit and so on.
1. Must mention code motion
#### Explaination
Calling extern function is blackbox that is compiler(and even user) cannot expect what happen.</br>
Then how can we ensure the safe of calling function. We want static value not valutile value.</br>
Then use local variables to store the function's returns</br>
These ensure we can use static value and Cashes do not need to read or write the functions so that make less cycle of cpu.</br>
And there are memory aliasing. Some of code will change the value of memory or free and so on. We can reduce the possibility as use local variables to store the values of memory.
2. Must mention compiler optimization blockers
#### Explaination
Improves speed due to reduced frequency of outloop execution.</br>
Another effect of this conversion is that constants can be stored in registers, and that each iteration does not require the address to be calculated and the memory (or cache line) to be accessed.</br>

3. Must mention loop unrolling
#### Explaination
 loop transformation technique that optimizes the execution speed of programs at the expense of binary size.</br>
 The conversion can be done manually through the programmer or the optimization compiler. </br>
#### Section to Provide file name and line numbers for all code related requirements.
code motion and compiler optimization blockers</br>
Triomino.cpp (line : 65~75)</br>
```cpp
sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::WindowIns().Getwindow());
	v2 pixelPosition = { static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y) };
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			mTri[r][c].cellType = CellInfo::Type::NOTHING;
			mTri[r][c].windowCenterPos = pixelPosition;
			mTri[r][c].UpdateSpritePos();
		}
	}
```
loop unrolling</br>
Triomino.cpp (line : 23~39)</br>
```cpp
for (int r = 0; r < TRIWIDTH; r++)
	{
		int i = 0;
		if (i < TRIHEIGHT)
		{
			mTri[r][i].boardPos = { (r - TRIWIDTH * 0.5f), (-TRIHEIGHT * 0.5f) };
			mTri[r][i].windowCenterPos = { (WindowInfo::WIDTH * 0.5f), (WindowInfo::HEIGHT * 0.5f) };
			mTri[r][i].cellType = CellInfo::Type::NOTHING;
			mTri[r][i+1].boardPos = { (r - TRIWIDTH * 0.5f), (1 - TRIHEIGHT * 0.5f) };
			mTri[r][i+1].windowCenterPos = { (WindowInfo::WIDTH * 0.5f), (WindowInfo::HEIGHT * 0.5f) };
			mTri[r][i+1].cellType = CellInfo::Type::NOTHING;
			mTri[r][i+2].boardPos = { (r - TRIWIDTH * 0.5f), (2 - TRIHEIGHT * 0.5f) };
			mTri[r][i+2].windowCenterPos = { (WindowInfo::WIDTH * 0.5f), (WindowInfo::HEIGHT * 0.5f) };
			mTri[r][i+2].cellType = CellInfo::Type::NOTHING;
		}
		i += TRIHEIGHT;
	}
```
3x3 loop unrolling</br>
Program optimization refers to the task of modifying a system to make any aspect of the task more effective or less resource-consuming.</br>
### CPU Caches           
In computer's storage(all storage include register. Dram, Sram and so on), data are read and written. The data are not move, physically, but are copied from other storage.</br>
However, Each storage have different cycle. In this case, How can we get more efficient work??</br>
There are two locality what we will explain. One is Temporal locality that reuse data already copied. The other is Spatial locality that contiguous memory address.</br>
1. Must mention the Memory Hierarchy
#### Explaination
Memory Hierarchy </br>
(High) cpu->register->cashe(lv1)->cashe(lv2)->...->main memory(dram)->HDD->...(Low) Process in order.</br>
register->cashe(lv1)->cashe(lv2)->...->main memory(drama)->HDD->...have the number of cycles in each cpu that increases exponentially as each storage is accessed.</br>
 ex) main memory about 10 cycle, HDD about 10000 cycle.</br>
Also more cheap more lower to price but more slower.</br>
The cycle is intended to ensure that each repository has data, and the more hits it has, the less frequently the cycle is.</br>
We can get benefit more use tomporal locality for hits.</br>
2. Must mention how a typical desktop Intel CPU is organized</br>
#### Explaination
Typical desktop Intel CPU is organized</br>
Each core processes data by incorporating the data in cashe(lv3) into its own controlled cashes.</br>
The use of this information is typological desktop Intel CPU organized.</br>
Our computer have 64bit size of cash block. Of course, The number of Cashes line and The number of blocks in the line is important.</br>
In this case, How we can get our goal?. Maybe Spatial locality will be needed...</br>
#### Example
Board.cpp (line : 20~35)</br>
```cpp
	{
    float halfWidth = WIDTH * 0.5f;
    float halfHeight = HEIGHT * 0.5f;
    Vector2 winCenter = Engine::WindowIns().GetSize();
    float halfWinX = winCenter.x * 0.5f;
    float halfWinY = winCenter.y * 0.5f;
    for (int r = 0; r < WIDTH; r++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            mBoard[r][c].boardPos = { (r - halfWidth), (c - halfHeight) };
            mBoard[r][c].windowCenterPos = { halfWinX, halfWinY };
            mBoard[r][c].cellType = CellInfo::Type::NORMAL;
        }
    }
}
```
In the code above, the repetitive nature of the for loop introduces temporal locality for r, c, mBoard of array (the base address of the array)</br>, as each of these variables is accessed within every iteration of the loop.</br>
Exploiting this spatial locality allows a system to load each variable from main memory only once into the CPU cache.</br>
Every subsequent access can be serviced out of the significantly faster cache. </br>
If memory data is stored by switching r and c, it will be stored very inefficiently.</br>
### Linking - Static Libraries & Shared Libraries
#### Explaination
Library is bunch of code. That have definit about classes, functions and so on. If we want to use some code, then use them link the library including them.(Can reuse only need library)</br>
There are two type of library, Static Library and Shared Library.</br>
| Type | Link-Time | identifier | explain |
| ---- | ----- | ------ | ------- |
| Static Library | compile time | .lib | After the code are compiled, all of them are linked(or interated) with library code. So that It cannot modified without re-compile |
| Shared Library | run time | .dll | If this file change to other dll, exe will do other work. It means a library that separates functions that multiple programs commonly need from programs so that they can only be called and written when necessary. |
#### Section to Provide file name and line numbers for all code related requirements.
dyn_array.lib : class-project-apple\AppleTeam\Debug or Release</br>
MathLibrary.dll(automatically) : class-project-apple\AppleTeam\Debug or Release</br>
WindowPos.dll(programmatically) : class-project-apple\AppleTeam\lib\Debug or Release</br>
WindowPos</br>
```cpp
#pragma once
#ifndef WINDOWPOS_H_
#define WINDOWPOS_H_

class WindowPos
{
    int GetUp(int y);
    int GetDown(int y);
};
#endif WINDOWPOS_H_
```
```cpp
#include "pch.h"
#include "WindowPos.h"

extern "C"
{
    __declspec(dllexport) int GetUp(int y)
    {
        return y + 1;
    }
    __declspec(dllexport) int GetDown(int y)
    {
        return y - 1;
    }
}
```
#### Section to Provide file name and line numbers for all code related requirements.</br></br>
## Proud of the topic
### Topic 1
Junseok Yang : [x] Linking - Static Libraries & Shared Libraries</br>
### Topic 2
Seungguk Jang :[x] C++ Core Guidelines on Pointers </br>
I consider about why it do need? is it better to use than before??</br>
And I realize what is pointer, what is swallow copy, what is deep copy and so on.</br>

## Section that describes work that was done to earn an Excellent score
### Topic 1
Junseok Yang : [x] Code Optimization</br>
Because while studying optimization, we understand why this approach is optimized and uses less cache memory. </br>
When applying optimization, there were conditions such as code motion, blockers, and loop unrolling, which all looked similar at first, but I felt that the more I searched and studied, the more different it was.</br> 
This is also related to cache memory, which I found many similarities when I created optimization and studied cache memory.</br> 
In conclusion, it took a lot of time to study optimization, apply it to the entire code, and I personally thought it was an interesting part. </br>
### Topic 2
Seungguk Jang :[x] C++ Core Guidelines on Pointers</br>
All about where I use.
