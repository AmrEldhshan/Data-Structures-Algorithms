// 20231157: Marawan Mohamed badr
// 20231116: Amr Khaled Ahmed
// 20230387: Marwan Mohamed Hassen
// 20230367: Mahmoud Ibraheem Mohamed

#include <iostream>

struct SuffixNode
{
    int ind;
    int r1;
    int r2;

    // --- Comparators for SuffixNode ---
    static bool compareByRank(const SuffixNode& a, const SuffixNode& b)
    {
        if (a.r1 != b.r1)
        {
            return a.r1 < b.r1;
        }
        return a.r2 < b.r2;
    }

    static bool compareByIndex(const SuffixNode& a, const SuffixNode& b)
    {
        return a.ind < b.ind;
    }

    [[nodiscard]] bool sameRanks(const SuffixNode& b) const
    {
        return (r1 == b.r1) && (r2 == b.r2);
    }
};

// --- Some helper functions ---
template<typename T>
void my_swap(T& a, T& b) noexcept
{
    T temp = a;
    a = b;
    b = temp;
}

int my_strlen(const char* s)
{
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

void my_strcpy(char* dest, const char* src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// --- Sort Function using HeapSort ---
template <typename T, bool (*Comparator)(const T&, const T&)>
void heapify_down(T* arr, int index, const int &size)
{
    while (true)
    {
        int largest = index;
        int left    = (index << 1) + 1;
        int right   = (index << 1) + 2;

        if (left < size && Comparator(arr[largest], arr[left]))
            largest = left;

        if (right < size && Comparator(arr[largest], arr[right]))
            largest = right;

        if (largest == index)
            break;

        my_swap(arr[largest], arr[index]);
        index = largest;
    }
}

template <typename T, bool (*Comparator)(const T&, const T&)>
void sort(T* arr, int n)
{
    // Build Max Heap
    for (int i = (n >> 1) - 1; i >= 0; i--)
        heapify_down<T,Comparator>(arr, i, n);

    // Extract elements
    while (n > 1)
    {
        my_swap(arr[0], arr[--n]);
        heapify_down<T,Comparator>(arr, 0, n);
    }
}

class SuffixArray
{
private:
    char* text;
    int length;
    SuffixNode* suffixes;

public:
    SuffixArray(const char* str)
    {
        length = my_strlen(str);
        text = new char[length + 1];
        my_strcpy(text, str);
        suffixes = new SuffixNode[length];
    }

    ~SuffixArray()
    {
        delete[] text;
        delete[] suffixes;
    }

    void ConstructUsingPrefixDoubling()
    {
        // Initialize suffixes with ranks
        for (int i = 0; i < length; i++)
        {
            suffixes[i].ind = i;
            suffixes[i].r1 = (unsigned char) text[i];
            suffixes[i].r2 = (i + 1 < length) ? (unsigned char) text[i + 1] : -1;
        }

        for (int k = 1; k < length; k *= 2)
        {
            // Sort by <r1, r2>
            sort<SuffixNode, SuffixNode::compareByRank>(suffixes, length);

            int* newRanks = new int[length];
            int rank = 0;
            newRanks[0] = 0;

            // Calculate new Rank1
            for (int i = 1; i < length; i++)
            {
                if (!suffixes[i].sameRanks(suffixes[i - 1]))
                    rank++;

                newRanks[i] = rank;
            }

            // Assign new Rank1
            for (int i = 0; i < length; i++)
            {
                suffixes[i].r1 = newRanks[i];
            }

            delete[] newRanks;

            // Sort by index to prepare for next iteration's r2 update
            sort<SuffixNode, SuffixNode::compareByIndex>(suffixes, length);

            // Assign new Rank2
            for (int i = 0; i < length; i++)
            {
                int nextIndex = suffixes[i].ind + k;
                if (nextIndex < length)
                {
                    suffixes[i].r2 = suffixes[nextIndex].r1;
                }
                else
                {
                    suffixes[i].r2 = -1;
                }
            }
        }

        // Final Sort by Rank
        sort<SuffixNode, SuffixNode::compareByRank>(suffixes, length);
    }

    void Print() const
    {
        for (int i = 0; i < length; i++)
        {
            printf("%d", suffixes[i].ind) ;
            if (i < length - 1)
            {
               printf(" ");
            }
        }
        printf("\n");
    }

};


int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}
