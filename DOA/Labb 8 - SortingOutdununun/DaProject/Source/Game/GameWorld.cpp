#include "stdafx.h"
#include "GameWorld.h"


#include <tga2d/math/vector2.h>
#include <tga2d/math/vector4.h>
#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include <CU/Heap/Heap.h>
#include <CU/Heap/Lesser.h>
#include "Renderer.h"

#include <CU/InputWrapper/SingletonInputWrapper.h>

size_t MaxValueNumber = 1000000;
size_t MaxElementsNumber = 10000000;

const size_t StartValue = 100;
const size_t StartElements = 1000000;


CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
}

void UpdateSpritesSizes(NumberArray & aArrayOfNumbers, SpriteArray & aArrayOfSprites)
{
	for (size_t iStaple = 0; iStaple < aArrayOfNumbers.Size(); ++iStaple)
	{
		aArrayOfSprites[iStaple]->SetSize(DX2D::Vector2f(1.f, -(static_cast<float>(aArrayOfNumbers[iStaple]) / static_cast<float>(MaxValueNumber)) * 10.f));
		const float ColorValue = static_cast<float>(aArrayOfNumbers[iStaple]) / static_cast<float>(MaxValueNumber);
		aArrayOfSprites[iStaple]->SetColor(DX2D::CColor(ColorValue, 1.f - ColorValue, 0.f, 1.f));
	}
}

void UpdateSpritesSizesOnOneIndex(NumberArray & aArrayOfNumbers, SpriteArray & aArrayOfSprites, const size_t aIndex)
{
	aArrayOfSprites[aIndex]->SetSize(DX2D::Vector2f(1.f, -(static_cast<float>(aArrayOfNumbers[aIndex]) / static_cast<float>(MaxValueNumber)) * 10.f));
	const float ColorValue = static_cast<float>(aArrayOfNumbers[aIndex]) / static_cast<float>(MaxValueNumber);
	aArrayOfSprites[aIndex]->SetColor(DX2D::CColor(ColorValue, 1.f - ColorValue, 0.f, 1.f));
}

void CGameWorld::Init()
{
	myText = new DX2D::CText("Text/calibril.ttf_sdf");

	myText->myText = "Press a key for desired number of elements:\n1. 1 - 1 000\n2. 1 - 10 000\n3. 1 - 100 000\n4. 1 - 1 000 000\n5. 1 - 10 000 000";
	myText->myPosition = DX2D::Vector2f(0.1f, 0.1f);

	myRenderer = new Renderer();
	myRenderer->Init();

	myThreads.Init(4);
	myState = eGameState::eChoosingElements;
}



void CGameWorld::Update(float /*aTimeDelta*/)
{ 
	CommonUtilities::SingletonInputWrapper::Update();
	switch (myState)
	{
	case eGameState::eChoosingElements:
		DecideNumberOfElements();
		break;
	case eGameState::eChoosingValues:
		DecideValueInterval();
		break;
	case eGameState::eStarting:
		StartAlgorithms();
		myState = eGameState::eRunning;
		break;
	case eGameState::eRunning:
		break;
	case eGameState::eFinished:
		break;
	}

	myRenderer->Render();
	myText->Render();
}

//void CGameWorld::SortWithHeap(StapleArray * aArrayOfNumbers)
//{
//	const DX2D::Vector2f StartPosition(0.f, 0.2f);
//	
//
//	CommonUtilities::Heap<Staple, size_t> tempHeap(*aArrayOfNumbers);
//	for (size_t iStaple = 0; iStaple < aArrayOfNumbers->Size(); ++iStaple)
//	{
//		tempHeap.HeapSort(*aArrayOfNumbers,iStaple);
//		FixPosition(*aArrayOfNumbers, StartPosition, DX2D::Vector2f(0.9f / static_cast<float>(aArrayOfNumbers->Size()), 0.f));
//	}
//}

void CGameWorld::SortWithInsert(NumberArray * aArrayOfNumbers, SpriteArray * aSpriteArray)
{
	const DX2D::Vector2f StartPosition(0.f, 0.2f);


	NumberArray tempArray;
	tempArray.Init(aArrayOfNumbers->Size());

	UpdateSpritesSizes(*aArrayOfNumbers, *aSpriteArray);


	for (size_t iStaple = 0; iStaple < aArrayOfNumbers->Size(); ++iStaple)
	{
		bool hasAdded = false;
		for (size_t iResult = 0; iResult < tempArray.Size(); ++iResult)
		{
			if ((*aArrayOfNumbers)[iStaple] < tempArray[iResult])
			{
				tempArray.Insert(iResult, (*aArrayOfNumbers)[iStaple]);

				UpdateSpritesSizes(tempArray, *aSpriteArray);

				hasAdded = true;
				break;
			}

		}

		if (hasAdded == false)
		{
			tempArray.Add((*aArrayOfNumbers)[iStaple]);
			UpdateSpritesSizes(tempArray, *aSpriteArray);
		}
	}

	bool exitGame = false;
	while (exitGame == false)
	{
	};
}

#pragma region Merge

/* left is the index of the leftmost element of the subarray; right is one
* past the index of the rightmost element */
void merge_helper(NumberArray & input, size_t left, size_t right, NumberArray & scratch, SpriteArray & aSpriteArray)
{
	/* base case: one element */
	if (right == left + 1)
	{
		return;
	}
	else
	{
		size_t i = 0;
		size_t length = right - left;
		size_t midpoint_distance = length / 2;
		/* l and r are to the positions in the left and right subarrays */
		size_t l = left, r = left + midpoint_distance;

		/* sort each subarray */
		merge_helper(input, left, left + midpoint_distance, scratch, aSpriteArray);
		merge_helper(input, left + midpoint_distance, right, scratch, aSpriteArray);

		/* merge the arrays together using scratch for temporary storage */
		for (i = 0; i < length; i++)
		{
			/* Check to see if any elements remain in the left array; if so,
			* we check if there are any elements left in the right array; if
			* so, we compare them.  Otherwise, we know that the merge must
			* use take the element from the left array */
			if (l < left + midpoint_distance &&
				(r == right || max(input[l], input[r]) == input[l]))
			{
				scratch[i] = input[l];
				l++;
			}
			else
			{
				scratch[i] = input[r];
				r++;
			}
			UpdateSpritesSizesOnOneIndex(scratch, aSpriteArray, i);
		}
		/* Copy the sorted subarray back to the input */
		for (i = left; i < right; i++)
		{
			input[i] = scratch[i - left];
		}
		//UpdateSpritesSizes(input, aSpriteArray);
	}
}

/* mergesort returns true on success.  Note that in C++, you could also
* replace malloc with new and if memory allocation fails, an exception will
* be thrown.  If we don't allocate a scratch array here, what happens?
*
* Elements are sorted in reverse order -- greatest to least */

void CGameWorld::SortWithMerge(NumberArray * input, size_t size, SpriteArray * aSpriteArray)
{
	NumberArray * scratch = new NumberArray(*input);
	UpdateSpritesSizes(*input, *aSpriteArray);
	//scratch->Init(MaxElementsNumber);
	merge_helper(*input, 0, size, *scratch, *aSpriteArray);
	UpdateSpritesSizes(*input, *aSpriteArray);
}

void CGameWorld::SortWithShell(NumberArray * aArray, SpriteArray * aSpriteArray)
{
	int gap, i, j, temp;

	UpdateSpritesSizes(*aArray, *aSpriteArray);

	for (gap = aArray->Size() / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < aArray->Size(); i++)
		{

			for (j = i - gap; j >= 0 && (*aArray)[j] > (*aArray)[j + gap]; j -= gap)
			{

				temp = (*aArray)[j];

				(*aArray)[j] = (*aArray)[j + gap];

				(*aArray)[j + gap] = temp;
				UpdateSpritesSizesOnOneIndex(*aArray, *aSpriteArray, j);
				UpdateSpritesSizesOnOneIndex(*aArray, *aSpriteArray, j + gap);
			}
		}
	}
	
	UpdateSpritesSizes(*aArray, *aSpriteArray);
}

#pragma endregion

//void quickSort(int arr[], int left, int right)
void CGameWorld::SortWithQuick(NumberArray * aArray, SpriteArray * aSpriteArray, int left, int right)
{
	//UpdateSpritesSizes(*aArray, *aSpriteArray);
	int i = left, j = right;
	int tmp;
	int pivot = (*aArray)[(left + right) / 2];

	/* partition */
	while (i <= j) 
	{
		while ((*aArray)[i] < pivot)
		{
			i++;
		}
		while ((*aArray)[j] > pivot)
		{
			j--;
		}
		if (i <= j) {
			tmp = (*aArray)[i];
			(*aArray)[i] = (*aArray)[j];
			(*aArray)[j] = tmp;
			UpdateSpritesSizesOnOneIndex(*aArray, *aSpriteArray, i);
			UpdateSpritesSizesOnOneIndex(*aArray, *aSpriteArray, j);

			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
	{
		SortWithQuick(aArray, aSpriteArray,  left, j);
	}
	if (i < right)
	{
		SortWithQuick(aArray, aSpriteArray, i, right);
	}

	//UpdateSpritesSizes(*aArray, *aSpriteArray);
}

void CGameWorld::CreateRandomStaples(NumberArray & aArrayOfNumbers, SpriteArray & aSpriteArray)
{
	for (size_t iNumber = 0; iNumber < MaxElementsNumber; ++iNumber)
	{
		size_t tempNumber = static_cast<size_t>(myRandomizer.GetRandomValue(1.f, static_cast<float>(MaxValueNumber)));
		aArrayOfNumbers.Add(tempNumber);
		DX2D::CSprite * tempSprite = new DX2D::CSprite(nullptr);
		tempSprite->SetPosition(DX2D::Vector2f(0.07f, 0.3f) + (DX2D::Vector2f(0.9f / static_cast<float>(MaxElementsNumber), 0.0f) * static_cast<float>(iNumber)));
		aSpriteArray.Add(tempSprite);
		myRenderer->AddSprite(*tempSprite);
	}
}



void CGameWorld::StartAlgorithms()
{
	NumberArray * tempStaple = new NumberArray();
	tempStaple->Init(MaxElementsNumber);

	SpriteArray * tempSprites = new SpriteArray();
	tempSprites->Init(MaxElementsNumber);

	CreateRandomStaples(*tempStaple, *tempSprites);

	//myThreads.Add(new std::thread(&CGameWorld::SortWithInsert, this, tempStaple, tempSprites));
	myThreads.Add(new std::thread(&CGameWorld::SortWithMerge, this, tempStaple, MaxElementsNumber, tempSprites));
	//myThreads.Add(new std::thread(&CGameWorld::SortWithShell, this, tempStaple, tempSprites));
	//myThreads.Add(new std::thread(&CGameWorld::SortWithHeap, this, tempStaple, tempSprites));
	//myThreads.Add(new std::thread(&CGameWorld::SortWithQuick, this, tempStaple, tempSprites, 0, MaxElementsNumber -1));
}

void CGameWorld::DecideNumberOfElements()
{
	DecidedElements();
	MaxElementsNumber = StartElements;

	if (GetInput::GetKeyPressed(DIK_1) == true)
	{
		DecidedElements();
		MaxElementsNumber = 1000;
	}
	else if (GetInput::GetKeyPressed(DIK_2) == true)
	{
		DecidedElements();
		MaxElementsNumber = 10000;
	}
	else if (GetInput::GetKeyPressed(DIK_3) == true)
	{
		DecidedElements();
		MaxElementsNumber = 100000;
	}
	else if (GetInput::GetKeyPressed(DIK_4) == true)
	{
		DecidedElements();
		MaxElementsNumber = 1000000;
	}
	else if (GetInput::GetKeyPressed(DIK_5) == true)
	{
		DecidedElements();
		MaxElementsNumber = 10000000;
	}
}


void CGameWorld::SortWithHeap(NumberArray * aArray, SpriteArray * aSpriteArray)
{
	UpdateSpritesSizes(*aArray, *aSpriteArray);

	int N = aArray->Size();
	int n = N, i = n / 2, parent, child;
	size_t t;

	while (true)
	{ /* Loops until arr is sorted */
		if (i > 0) { /* First stage - Sorting the heap */
			i--;           /* Save its index to i */
			t = (*aArray)[i];    /* Save parent value to t */
		}
		else {     /* Second stage - Extracting elements in-place */
			n--;           /* Make the new heap smaller */
			if (n == 0)
			{
				UpdateSpritesSizes(*aArray, *aSpriteArray);
				return; /* When the heap is empty, we are done */
			}
				
			t = (*aArray)[n];    /* Save last value (it will be overwritten) */
			(*aArray)[n] = (*aArray)[0]; /* Save largest value at the end of arr */
		}

		parent = i; /* We will start pushing down t from parent */
		child = i * 2 + 1; /* parent's left child */

						   /* Sift operation - pushing the value of t down the heap */
		while (child < n) {
			if (child + 1 < n  && (*aArray)[child + 1] > (*aArray)[child]) {
				child++; /* Choose the largest child */
			}
			if ((*aArray)[child] > t) { /* If any child is bigger than the parent */
				(*aArray)[parent] = (*aArray)[child]; /* Move the largest child up */
				parent = child; /* Move parent pointer to this child */
				child = parent * 2 + 1; /* Find the next child */

				UpdateSpritesSizesOnOneIndex(*aArray, *aSpriteArray, parent);
				//UpdateSpritesSizesOnOneIndex(*aArray, *aSpriteArray, child);
			}
			else {
				break; /* t's place is found */
			}
		}
		(*aArray)[parent] = t; /* We save t in the heap */
						 //std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

void CGameWorld::DecidedElements()
{
	myText->myText = "Press a key for desired values interval:\n1. 1 - 10\n2. 1 - 1 000\n3. 1 - 100 000\n4. 1 - 100 000 000";
	myState = eGameState::eChoosingValues;
}

void CGameWorld::DecideValueInterval()
{
	DecidedValues();
	MaxValueNumber = StartValue;

	if (GetInput::GetKeyPressed(DIK_1) == true)
	{
		DecidedValues();
		MaxValueNumber = 10;
	}
	else if (GetInput::GetKeyPressed(DIK_2) == true)
	{
		DecidedValues();
		MaxValueNumber = 1000;
	}
	else if (GetInput::GetKeyPressed(DIK_3) == true)
	{
		DecidedValues();
		MaxValueNumber = 100000;
	}
	else if (GetInput::GetKeyPressed(DIK_4) == true)
	{
		DecidedValues();
		MaxValueNumber = 100000000;
	}
}

void CGameWorld::DecidedValues()
{
	myText->myText = "";
	myState = eGameState::eStarting;
}

Staple::Staple(size_t aNumber)
{
	myNumber = aNumber;

	mySprite = new DX2D::CSprite(nullptr);
	mySprite->SetPosition(DX2D::Vector2f(1.f, 0.2f));
	mySprite->SetSize(DX2D::Vector2f(1.f, -(static_cast<float>(aNumber) / static_cast<float>(MaxValueNumber)) * 10.f));

	const float ColorValue = static_cast<float>(myNumber) / static_cast<float>(MaxValueNumber);
	mySprite->SetColor(DX2D::CColor(ColorValue, 1.f - ColorValue, 0.f, 1.f));
}

Staple::Staple()
{
	mySprite = nullptr;
}
