// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2010, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: Manuel Holtgrewe <manuel.holtgrewe@fu-berlin.de>
// ==========================================================================

#ifndef SEQAN_CORE_TESTS_ALIGN_TEST_ALIGN_GAPS_H_
#define SEQAN_CORE_TESTS_ALIGN_TEST_ALIGN_GAPS_H_

#include <sstream>

#include <seqan/align.h>

// ==========================================================================
// Generic Tests For Gaps Specializations
// ==========================================================================

// --------------------------------------------------------------------------
// Test Metafunctions.
// --------------------------------------------------------------------------

// Test metafunctions interface of Array Gaps.

template <typename TGapsSpec>
void testAlignGapsMetafunctions(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String               TString;
    typedef Gaps<TString, TGapsSpec> TGaps;

    // We only check that we can call these metafunctions.  We should also test
    // for expected resulting types.  This could/should be done with concept
    // checking.

    // Hosted Type metafunctions.
    typedef typename Source<TGaps>::Type             TSource;

    // Sequence metafunctions.
    typedef typename Difference<TGaps>::Type         TDifference;
    typedef typename GetValue<TGaps>::Type           TGetValue;
    typedef typename Iterator<TGaps, Rooted>::Type   TRootedIterator;
    typedef typename Iterator<TGaps, Standard>::Type TStandardIterator;
    typedef typename Position<TGaps>::Type           TPosition;
    typedef typename Reference<TGaps>::Type          TReference;
    typedef typename Size<TGaps>::Type               TSize;
    typedef typename Value<TGaps>::Type              TValue;
}

// --------------------------------------------------------------------------
// Test Hosted Type Interface Of Array Gaps.
// --------------------------------------------------------------------------

// Test behaviour of constructor and setting of source with different
// arguments.

template <typename TGapsSpec>
void testAlignGapsConstructorAndSource(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    // Check with non-const string.
    {
        typedef Dna5String              TString;
        typedef Gaps<TString, TGapsSpec> TGaps;

        TString seq("AAAAACCCCC");
        TGaps gaps(seq);

        SEQAN_ASSERT_EQ(&source(gaps), &seq);
        SEQAN_ASSERT_EQ(source(gaps), seq);
    }

    // Check with const string.
    {
        typedef Dna5String                     TString;
        typedef Gaps<TString const, TGapsSpec> TGaps;

        TString seq("AAAAACCCCC");
        TGaps gaps(seq);

        SEQAN_ASSERT_EQ(&source(gaps), &seq);
        SEQAN_ASSERT_EQ(source(gaps), seq);
    }
}

// Test setSource() function of Array Gaps.


template <typename TGapsSpec>
void testAlignGapsSetSource(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    // Check with non-const string.
    {
        typedef Dna5String               TString;
        typedef Gaps<TString, TGapsSpec> TGaps;

        TString seq("AAAAACCCCC");
        TGaps gaps;

        setSource(gaps, seq);

        SEQAN_ASSERT_EQ(&source(gaps), &seq);
        SEQAN_ASSERT_EQ(source(gaps), seq);
    }

    // Check with const string.
    {
        typedef Dna5String                     TString;
        typedef Gaps<TString const, TGapsSpec> TGaps;

        TString seq("AAAAACCCCC");
        TGaps gaps;

        setSource(gaps, seq);

        SEQAN_ASSERT_EQ(&source(gaps), &seq);
        SEQAN_ASSERT_EQ(source(gaps), seq);
    }
}

// Test assignSource() function of Array Gaps.

template <typename TGapsSpec>
void testAlignGapsAssignSource(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    // Check with non-const string.
    {
        typedef Dna5String               TString;
        typedef Gaps<TString, TGapsSpec> TGaps;

        TString seq("AAAAACCCCC");
        TGaps gaps;

        setSource(gaps, seq);

        SEQAN_ASSERT_EQ(&source(gaps), &seq);
        SEQAN_ASSERT_EQ(source(gaps), seq);
    }

    // Note: Checking with const-string makes no sense.
}

// --------------------------------------------------------------------------
// Test Gap Query/Mutation Interface Of Array Gaps.
// --------------------------------------------------------------------------

// Test insertion, deletion, querying of gaps with Array Gaps object with
// gaps in the center.

template <typename TGapsSpec>
void testAlignGapsGapOperationsGapCenter(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String               TString;
    typedef Gaps<TString, TGapsSpec> TGaps;

    // Note: The string's characters are chosen such that it is clear from which
    // part of the char is from by its value, i.e. A = left, C = left adjacent
    // to gaps etc.

    // Insert one gap in the center and do queries on the result.
    {
        TString seq("AAACGTTT");
        TGaps gaps(seq);
        
        insertGap(gaps, 4);

        SEQAN_ASSERT_EQ(length(seq), 8u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        SEQAN_ASSERT(gaps[3] == 'C');
        SEQAN_ASSERT(gaps[4] == '-');
        SEQAN_ASSERT(gaps[5] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 3));
        SEQAN_ASSERT(isGap(gaps, 4));
        SEQAN_ASSERT_NOT(isGap(gaps, 5));
    }

    // Insert two gaps in the center and do queries on the result.
    {
        TString seq("AAACGTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 4, 2);

        SEQAN_ASSERT_EQ(length(seq), 8u);
        SEQAN_ASSERT_EQ(length(gaps), 10u);

        // Query sequence.
        SEQAN_ASSERT(gaps[3] == 'C');
        SEQAN_ASSERT(gaps[4] == '-');
        SEQAN_ASSERT(gaps[5] == '-');
        SEQAN_ASSERT(gaps[6] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 3));
        SEQAN_ASSERT(isGap(gaps, 4));
        SEQAN_ASSERT(isGap(gaps, 5));
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
    }

    // Insert three gaps in the center, remove one, then perform queries.
    {
        TString seq("AAACGTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 4, 3);
        SEQAN_ASSERT_EQ(removeGap(gaps, 4), 1u);

        SEQAN_ASSERT_EQ(length(seq), 8u);
        SEQAN_ASSERT_EQ(length(gaps), 10u);

        // Query sequence.
        SEQAN_ASSERT(gaps[3] == 'C');
        // SEQAN_ASSERT(gaps[4] == '-');
        // SEQAN_ASSERT(gaps[5] == '-');
        SEQAN_ASSERT(gaps[6] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 3));
        SEQAN_ASSERT(isGap(gaps, 4));
        SEQAN_ASSERT(isGap(gaps, 5));
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
    }

    // Insert four gaps in the center, remove one, then perform queries.
    {
        TString seq("AAACGTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 4, 4);
        SEQAN_ASSERT_EQ(removeGaps(gaps, 4, 2), 2u);

        SEQAN_ASSERT_EQ(length(seq), 8u);
        SEQAN_ASSERT_EQ(length(gaps), 10u);

        // Query sequence.
        SEQAN_ASSERT(gaps[3] == 'C');
        // SEQAN_ASSERT(gaps[4] == '-');
        // SEQAN_ASSERT(gaps[5] == '-');
        SEQAN_ASSERT(gaps[6] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 3));
        SEQAN_ASSERT(isGap(gaps, 4));
        SEQAN_ASSERT(isGap(gaps, 5));
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
    }

    // Insert gaps in the center, then clear.
    {
        TString seq("AAACGTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 4, 4);
        clearGaps(gaps);

        SEQAN_ASSERT_EQ(length(seq), 8u);
        SEQAN_ASSERT_EQ(length(gaps), 8u);

        // Query sequence.
        SEQAN_ASSERT(gaps[2] == 'A');
        SEQAN_ASSERT(gaps[3] == 'C');
        SEQAN_ASSERT(gaps[4] == 'G');
        SEQAN_ASSERT(gaps[5] == 'T');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 2));
        SEQAN_ASSERT_NOT(isGap(gaps, 3));
        SEQAN_ASSERT_NOT(isGap(gaps, 4));
        SEQAN_ASSERT_NOT(isGap(gaps, 5));
    }
}

// Test insertion, deletion, querying of gaps with Array Gaps object with
// leading gaps.

// TODO(holtgrew): What if more gaps should be removed than there are?

template <typename TGapsSpec>
void testAlignGapsGapOperationsGapsLeading(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String               TString;
    typedef Gaps<TString, TGapsSpec> TGaps;

    // Note: The string's characters are chosen such that it is clear from which
    // part of the char is from by its value, i.e. G = right adjacent to gap,
    // T = right of gap.

    // Insert one gap at the beginning and do queries on the result.
    {
        TString seq("GTTTTTT");
        TGaps gaps(seq);

        insertGap(gaps, 0);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 8u);

        // Query sequence.
        // SEQAN_ASSERT(gaps[0] == '-');
        SEQAN_ASSERT(gaps[1] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT(isGap(gaps, 0));
        SEQAN_ASSERT_NOT(isGap(gaps, 1));
    }

    // Insert two gaps at the beginning and do queries on the result.
    {
        TString seq("GTTTTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 0, 2);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        // SEQAN_ASSERT(gaps[0] == '-');
        // SEQAN_ASSERT(gaps[1] == '-');
        SEQAN_ASSERT(gaps[2] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT(isGap(gaps, 0));
        SEQAN_ASSERT(isGap(gaps, 1));
        SEQAN_ASSERT_NOT(isGap(gaps, 2));
    }

    // Insert three gaps at the beginning, remove one, then perform queries.
    {
        TString seq("GTTTTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 0, 3);
        SEQAN_ASSERT_EQ(removeGap(gaps, 0), 1u);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        // SEQAN_ASSERT(gaps[0] == '-');
        // SEQAN_ASSERT(gaps[1] == '-');
        SEQAN_ASSERT(gaps[2] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT(isGap(gaps, 0));
        SEQAN_ASSERT(isGap(gaps, 1));
        SEQAN_ASSERT_NOT(isGap(gaps, 2));
    }

    // Insert four gaps at the beginning, remove one, then perform queries.
    {
        TString seq("GTTTTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 0, 4);
        SEQAN_ASSERT_EQ(removeGaps(gaps, 0, 2), 2u);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        // SEQAN_ASSERT(gaps[0] == '-');
        // SEQAN_ASSERT(gaps[1] == '-');
        SEQAN_ASSERT(gaps[2] == 'G');
        
        // Query gaps.
        SEQAN_ASSERT(isGap(gaps, 0));
        SEQAN_ASSERT(isGap(gaps, 1));
        SEQAN_ASSERT_NOT(isGap(gaps, 2));
    }

    // Insert gaps at the beginning, then clear.
    {
        TString seq("GTTTTTT");
        TGaps gaps(seq);
        
        insertGaps(gaps, 0, 4);
        clearGaps(gaps);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 7u);

        // Query sequence.
        SEQAN_ASSERT(gaps[0] == 'G');
        SEQAN_ASSERT(gaps[1] == 'T');
        SEQAN_ASSERT(gaps[2] == 'T');
        SEQAN_ASSERT(gaps[3] == 'T');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 3));
        SEQAN_ASSERT_NOT(isGap(gaps, 4));
        SEQAN_ASSERT_NOT(isGap(gaps, 5));
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
    }
}

// Test insertion, deletion, querying of gaps with Array Gaps object with
// trailing gaps.

template <typename TGapsSpec>
void testAlignGapsGapOperationsGapsTrailing(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String               TString;
    typedef Gaps<TString, TGapsSpec> TGaps;

    // Note: The string's characters are chosen such that it is clear from which
    // part of the char is from by its value, i.e. A = left of gap, C = left
    // adjacent with gap.

    // Insert one gap at the end and do queries on the result.
    {
        TString seq("AAAAAAC");
        TGaps gaps(seq);
        
        insertGap(gaps, 7);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 8u);

        // Query sequence.
        SEQAN_ASSERT(gaps[6] == 'C');
        // SEQAN_ASSERT(gaps[7] == '-');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
        SEQAN_ASSERT(isGap(gaps, 7));
    }

    // Insert two gaps at the end and do queries on the result.
    {
        TString seq("AAAAAAC");
        TGaps gaps(seq);
        
        insertGaps(gaps, 7, 2);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        SEQAN_ASSERT(gaps[6] == 'C');
        // SEQAN_ASSERT(gaps[7] == '-');
        // SEQAN_ASSERT(gaps[8] == '-');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
        SEQAN_ASSERT(isGap(gaps, 7));
        SEQAN_ASSERT(isGap(gaps, 8));
    }

    // Insert three gaps at the end, remove one, then perform queries.
    {
        TString seq("AAAAAAC");
        TGaps gaps(seq);
        
        insertGaps(gaps, 7, 3);
        SEQAN_ASSERT_EQ(removeGap(gaps, 7), 1u);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        SEQAN_ASSERT(gaps[6] == 'C');
        // SEQAN_ASSERT(gaps[7] == '-');
        // SEQAN_ASSERT(gaps[8] == '-');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
        SEQAN_ASSERT(isGap(gaps, 7));
        SEQAN_ASSERT(isGap(gaps, 8));
    }

    // Insert four gaps at the end, remove two, then perform queries.
    {
        TString seq("AAAAAAC");
        TGaps gaps(seq);
        
        insertGaps(gaps, 7, 4);
        SEQAN_ASSERT_EQ(removeGaps(gaps, 7, 2), 2u);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 9u);

        // Query sequence.
        SEQAN_ASSERT(gaps[6] == 'C');
        // SEQAN_ASSERT(gaps[7] == '-');
        // SEQAN_ASSERT(gaps[8] == '-');
        
        // Query gaps.
        SEQAN_ASSERT_NOT(isGap(gaps, 6));
        SEQAN_ASSERT(isGap(gaps, 7));
        SEQAN_ASSERT(isGap(gaps, 8));
    }

    // Insert gaps at the end, then clear.
    {
        TString seq("AAAAAAC");
        TGaps gaps(seq);
        
        insertGaps(gaps, 7, 4);
        clearGaps(gaps);

        SEQAN_ASSERT_EQ(length(seq), 7u);
        SEQAN_ASSERT_EQ(length(gaps), 7u);
    }
}

// --------------------------------------------------------------------------
// Test Sequence Interface Of Array Gaps.
// --------------------------------------------------------------------------

// TODO(holtgrew): Once the sequence concept has been fixed, revisit and test all functions!

// Test treating Array Gaps object like a sequence; without gaps.

template <typename TGapsSpec>
void testAlignGapsSequenceInterfaceUngapped(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                              TString;
    typedef Gaps<TString, TGapsSpec>                TGaps;
    typedef typename Iterator<TGaps, Rooted>::Type  TGapsIter;

    TString seq("ACGT");
    TGaps gaps(seq);

    // Test length.
    SEQAN_ASSERT_EQ(length(seq), 4u);
    SEQAN_ASSERT_EQ(length(gaps), 4u);

    // Test random access with subscription operator.
    SEQAN_ASSERT(gaps[0] == 'A');
    SEQAN_ASSERT(gaps[1] == 'C');
    SEQAN_ASSERT(gaps[2] == 'G');
    SEQAN_ASSERT(gaps[3] == 'T');

    // Test iteration.
    CharString res;

    // Test stream operator, concatenation of characters/gaps.
    std::stringstream ss;
    ss << gaps;
    SEQAN_ASSERT_EQ(ss.str(), "ACGT");
}

// Test treating Array Gaps object like a sequence; with gaps in the center.

template <typename TGapsSpec>
void testAlignGapsSequenceInterfaceGapsCenter(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                              TString;
    typedef Gaps<TString, TGapsSpec>                TGaps;
    typedef typename Iterator<TGaps, Rooted>::Type  TGapsIter;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 2);

    // Test length.
    SEQAN_ASSERT_EQ(length(seq), 4u);
    SEQAN_ASSERT_EQ(length(gaps), 5u);

    // Test random access with subscription operator.
    SEQAN_ASSERT(gaps[0] == 'A');
    SEQAN_ASSERT(gaps[1] == 'C');
    SEQAN_ASSERT(gaps[2] == '-');
    SEQAN_ASSERT(gaps[3] == 'G');
    SEQAN_ASSERT(gaps[4] == 'T');

    // Test iteration.
    CharString res;

    // Test stream operator, concatenation of characters/gaps.
    std::stringstream ss;
    ss << gaps;
    SEQAN_ASSERT_EQ(ss.str(), "AC-GT");
}

// Test treating Array Gaps object like a sequence; with leading gaps.

template <typename TGapsSpec>
void testAlignGapsSequenceInterfaceGapsLeading(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                              TString;
    typedef Gaps<TString, TGapsSpec>                TGaps;
    typedef typename Iterator<TGaps, Rooted>::Type  TGapsIter;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 0);

    // Test length.
    SEQAN_ASSERT_EQ(length(seq), 4u);
    SEQAN_ASSERT_EQ(length(gaps), 5u);

    // Test random access with subscription operator.
    SEQAN_ASSERT(gaps[0] == '-');
    SEQAN_ASSERT(gaps[1] == 'A');
    SEQAN_ASSERT(gaps[2] == 'C');
    SEQAN_ASSERT(gaps[3] == 'G');
    SEQAN_ASSERT(gaps[4] == 'T');

    // Test iteration.
    CharString res;

    // Test stream operator, concatenation of characters/gaps.
    std::stringstream ss;
    ss << gaps;
    SEQAN_ASSERT_EQ(ss.str(), "-ACGT");
}

// Test treating Array Gaps object like a sequence; with trailing gaps.

template <typename TGapsSpec>
void testAlignGapsSequenceInterfaceGapsTrailing(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 4);

    // Test length.
    SEQAN_ASSERT_EQ(length(seq), 4u);
    SEQAN_ASSERT_EQ(length(gaps), 5u);

    // Test random access with subscription operator.
    SEQAN_ASSERT(gaps[0] == 'A');
    SEQAN_ASSERT(gaps[1] == 'C');
    SEQAN_ASSERT(gaps[2] == 'G');
    SEQAN_ASSERT(gaps[3] == 'T');
    SEQAN_ASSERT(gaps[4] == '-');

    // Test iteration.
    CharString res;

    // Test stream operator, concatenation of characters/gaps.
    std::stringstream ss;
    ss << gaps;
    SEQAN_ASSERT_EQ(ss.str(), "ACGT-");
}

// Test begin() function for Array Gaps.
template <typename TGapsSpec>
void testAlignGapsIteratorInterfaceBegin(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                               TString;
    typedef Gaps<TString, TGapsSpec>                 TGaps;
    typedef typename Iterator<TGaps, Standard>::Type TStandardGapsIter;
    typedef typename Iterator<TGaps, Rooted>::Type   TRootedGapsIter;

    TString seq("ACGT");
    TGaps gaps(seq);

    TStandardGapsIter itS = begin(gaps, Standard());
    SEQAN_ASSERT_EQ(*itS, 'A');

    TRootedGapsIter itR = begin(gaps, Rooted());
    SEQAN_ASSERT_EQ(*itR, 'A');
}

// Test end() function for Array Gaps.
template <typename TGapsSpec>
void testAlignGapsIteratorInterfaceEnd(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                               TString;
    typedef Gaps<TString, TGapsSpec>                 TGaps;
    typedef typename Iterator<TGaps, Standard>::Type TStandardGapsIter;
    typedef typename Iterator<TGaps, Rooted>::Type   TRootedGapsIter;

    TString seq("ACGT");
    TGaps gaps(seq);

    TStandardGapsIter itS = end(gaps, Standard());
    --itS;
    SEQAN_ASSERT_EQ(*itS, 'T');

    TRootedGapsIter itR = end(gaps, Rooted());
    --itR;
    SEQAN_ASSERT_EQ(*itR, 'T');
}

// Test iter() function for Array Gaps.
template <typename TGapsSpec>
void testAlignGapsIteratorInterfaceIter(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                               TString;
    typedef Gaps<TString, TGapsSpec>                 TGaps;
    typedef typename Iterator<TGaps, Standard>::Type TStandardGapsIter;
    typedef typename Iterator<TGaps, Rooted>::Type   TRootedGapsIter;

    TString seq("ACGT");
    TGaps gaps(seq);

    TStandardGapsIter itS = iter(gaps, 2, Standard());
    SEQAN_ASSERT_EQ(*itS, 'G');

    TRootedGapsIter itR = iter(gaps, 2, Rooted());
    SEQAN_ASSERT_EQ(*itR, 'G');
}

// --------------------------------------------------------------------------
// Test Source/View Position Interface Of Array Gaps.
// --------------------------------------------------------------------------

// Test source/view position of Array Gaps object; without gaps.

template <typename TGapsSpec>
void testAlignGapsSourceViewPositionUngapped(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), 0);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 2);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 3);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 0u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 3), 3u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 4), 4u);
}

// Test source/view position of Array Gaps object; center gaps.

template <typename TGapsSpec>
void testAlignGapsSourceViewPositionGapsCenter(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 2);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), 0);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 3);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 4);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 0u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 3), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 4), 3u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 5), 4u);
}

// Test source/view position of Array Gaps object; leading gaps.

template <typename TGapsSpec>
void testAlignGapsSourceViewPositionGapsLeading(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 0);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 2);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 3);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 4);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 0u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 0u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 3), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 4), 3u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 5), 4u);
}

// Test source/view position of Array Gaps object; trailing gaps.

template <typename TGapsSpec>
void testAlignGapsSourceViewPositionGapsTrailing(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 4);

    // 01234
    // ACGT-

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), 0);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 2);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 3);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 0u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 3), 3u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 4), 4u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 5), 4u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 6), 4u);
}

// --------------------------------------------------------------------------
// Test Clipping Interface Of Array Gaps.
// --------------------------------------------------------------------------

// Test treating Array Gaps object like a sequence without gaps.  Use clipping.

template <typename TGapsSpec>
void testAlignGapsClippingUngapped(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    setClippedBeginPosition(gaps, 1);
    setClippedEndPosition(gaps, 3);

    // 0123
    // ACGT
    //  XX

    SEQAN_ASSERT_EQ(length(gaps), 2u);
    SEQAN_ASSERT_EQ(unclippedLength(gaps), 4u);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), -1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 0);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 2);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 2u);

    SEQAN_ASSERT_EQ(clippedBeginPosition(gaps), 1);
    SEQAN_ASSERT_EQ(clippedEndPosition(gaps), 3);

    SEQAN_ASSERT_EQ(beginPosition(gaps), 1u);
    SEQAN_ASSERT_EQ(endPosition(gaps), 3u);
}

// Test treating Array Gaps object like a sequence having gaps in the center of
// the clipping.

template <typename TGapsSpec>
void testAlignGapsClippingGapsCenter(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    insertGap(gaps, 2);

    // 01234
    // AC-GT
    //  XXX

    setClippedBeginPosition(gaps, 1);
    setClippedEndPosition(gaps, 4);

    SEQAN_ASSERT_EQ(length(gaps), 3u);
    SEQAN_ASSERT_EQ(unclippedLength(gaps), 5u);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), -1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 0);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 2);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 3);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 2u);

    SEQAN_ASSERT_EQ(clippedBeginPosition(gaps), 1);
    SEQAN_ASSERT_EQ(clippedEndPosition(gaps), 4);

    SEQAN_ASSERT_EQ(beginPosition(gaps), 1u);
    SEQAN_ASSERT_EQ(endPosition(gaps), 3u);
}

// Test treating Array Gaps object like a sequence having leading gaps in the
// clipping.

template <typename TGapsSpec>
void testAlignGapsClippingGapsLeading(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    // 012345
    // A--CGT
    //   XXXX

    insertGaps(gaps, 1, 2);

    setClippedBeginPosition(gaps, 2);
    setClippedEndPosition(gaps, 6);

    SEQAN_ASSERT_EQ(length(gaps), 4u);
    SEQAN_ASSERT_EQ(unclippedLength(gaps), 6u);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), -2);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 2);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 3), 3);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 3), 3u);

    SEQAN_ASSERT_EQ(clippedBeginPosition(gaps), 2);
    SEQAN_ASSERT_EQ(clippedEndPosition(gaps), 6);

    SEQAN_ASSERT_EQ(clippedBeginPosition(gaps), 2);
    SEQAN_ASSERT_EQ(clippedEndPosition(gaps), 6);

    SEQAN_ASSERT_EQ(beginPosition(gaps), 1u);
    SEQAN_ASSERT_EQ(endPosition(gaps), 4u);
}

// Test treating Array Gaps object like a sequence having trailing gaps in the
// clipping.

template <typename TGapsSpec>
void testAlignGapsClippingGapsTrailing(TGapsSpec const & /*spec*/)
{
    using namespace seqan;

    typedef Dna5String                     TString;
    typedef Gaps<TString, TGapsSpec>       TGaps;

    TString seq("ACGT");
    TGaps gaps(seq);

    // 012345
    // ACG--T
    // XXXX

    insertGaps(gaps, 3, 2);

    setClippedBeginPosition(gaps, 0);
    setClippedEndPosition(gaps, 4);

    SEQAN_ASSERT_EQ(length(gaps), 4u);
    SEQAN_ASSERT_EQ(unclippedLength(gaps), 6u);

    SEQAN_ASSERT_EQ(toViewPosition(gaps, 0), 0);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 1), 1);
    SEQAN_ASSERT_EQ(toViewPosition(gaps, 2), 2);

    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 0), 0u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 1), 1u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 2), 2u);
    SEQAN_ASSERT_EQ(toSourcePosition(gaps, 3), 3u);

    SEQAN_ASSERT_EQ(clippedBeginPosition(gaps), 0);
    SEQAN_ASSERT_EQ(clippedEndPosition(gaps), 4);

    SEQAN_ASSERT_EQ(beginPosition(gaps), 0u);
    SEQAN_ASSERT_EQ(endPosition(gaps), 3u);
}

// ==========================================================================
// Tests for Array Gaps
// ==========================================================================

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_metafunctions)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsMetafunctions(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_constructor_and_source)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsConstructorAndSource(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_set_source)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSetSource(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_assign_source)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsAssignSource(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_gap_operations_gaps_center)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsGapOperationsGapCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_gap_operations_gaps_leading)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsGapOperationsGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_gap_operations_gaps_trailing)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsGapOperationsGapsTrailing(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_sequence_interface_ungapped)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSequenceInterfaceUngapped(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_sequence_interface_gaps_center)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSequenceInterfaceGapsCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_sequence_interface_gaps_leading)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSequenceInterfaceGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_sequence_interface_gaps_trailing)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSequenceInterfaceGapsTrailing(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_iterator_interface_begin)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsIteratorInterfaceBegin(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_iterator_interface_end)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsIteratorInterfaceEnd(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_iterator_interface_iter)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsIteratorInterfaceIter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_source_view_position_ungapped)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSourceViewPositionUngapped(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_source_view_position_gaps_center)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSourceViewPositionGapsCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_source_view_position_gaps_leading)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSourceViewPositionGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_source_view_position_gaps_trailing)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsSourceViewPositionGapsTrailing(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_clipping_ungapped)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsClippingUngapped(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_clipping_gaps_center)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsClippingGapsCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_clipping_gaps_leading)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsClippingGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_array_gaps_clipping_gaps_trailing)
{
    using namespace seqan;
    typedef ArrayGaps TTag;
    testAlignGapsClippingGapsTrailing(TTag());
}

// ==========================================================================
// Tests for Anchor Gaps
// ==========================================================================

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_metafunctions)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsMetafunctions(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_constructor_and_source)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsConstructorAndSource(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_set_source)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSetSource(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_assign_source)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsAssignSource(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_gap_operations_gaps_center)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsGapOperationsGapCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_gap_operations_gaps_leading)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsGapOperationsGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_gap_operations_gaps_trailing)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsGapOperationsGapsTrailing(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_sequence_interface_ungapped)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSequenceInterfaceUngapped(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_sequence_interface_gaps_center)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSequenceInterfaceGapsCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_sequence_interface_gaps_leading)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSequenceInterfaceGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_sequence_interface_gaps_trailing)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSequenceInterfaceGapsTrailing(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_iterator_interface_begin)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsIteratorInterfaceBegin(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_iterator_interface_end)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsIteratorInterfaceEnd(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_iterator_interface_iter)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsIteratorInterfaceIter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_source_view_position_ungapped)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSourceViewPositionUngapped(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_source_view_position_gaps_center)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSourceViewPositionGapsCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_source_view_position_gaps_leading)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSourceViewPositionGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_source_view_position_gaps_trailing)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsSourceViewPositionGapsTrailing(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_clipping_ungapped)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsClippingUngapped(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_clipping_gaps_center)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsClippingGapsCenter(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_clipping_gaps_leading)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsClippingGapsLeading(TTag());
}

SEQAN_DEFINE_TEST(test_align_gaps_anchor_gaps_clipping_gaps_trailing)
{
    using namespace seqan;
    typedef AnchorGaps<> TTag;
    testAlignGapsClippingGapsTrailing(TTag());
}

#endif  // #ifndef SEQAN_CORE_TESTS_ALIGN_TEST_ALIGN_GAPS_H_