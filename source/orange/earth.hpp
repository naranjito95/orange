
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// A copy of the GNU General Public License is available at
// http://www.r-project.org/Licenses

/*
    This file is part of Orange.

    Copyright 1996-2011 Faculty of Computer and Information Science, University of Ljubljana
    Contact: janez.demsar@fri.uni-lj.si

    Orange is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Orange is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Orange.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 	 Changes to earth.h from earth R package:
 	 - Added defines for STANDALONE USING_R
 	 - Removed definition for bool

 */


#ifndef __EARTH_HPP
#define __EARTH_HPP

#define STANDALONE 1
#define USING_R 0

#if USING_R

void FreeR(void);

void ForwardPassR(              // for use by R
    int    FullSet[],           // out: nMaxTerms x 1, bool vec of lin indep cols of bx
    double bx[],                // out: MARS basis matrix, nCases x nMaxTerms
    double Dirs[],              // out: nMaxTerms x nPreds, elements are -1,0,1,2
    double Cuts[],              // out: nMaxTerms x nPreds, cut for iTerm,iPred
    const double x[],           // in: nCases x nPreds
    const double y[],           // in: nCases x nResp
    const double WeightsArg[],  // in: nCases x 1, can be R_NilValue, currently ignored
    const int *pnCases,         // in: number of rows in x and elements in y
    const int *pnResp,          // in: number of cols in y
    const int *pnPreds,         // in: number of cols in x
    const int *pnMaxDegree,     // in:
    const int *pnMaxTerms,      // in:
    const double *pPenalty,     // in:
    double *pThresh,            // in: forward step threshold
    const int *pnMinSpan,       // in:
    const int *pnFastK,         // in: Fast MARS K
    const double *pFastBeta,    // in: Fast MARS ageing coef
    const double *pNewVarPenalty, // in: penalty for adding a new variable (default is 0)
    const int  LinPreds[],        // in: nPreds x 1, 1 if predictor must enter linearly
    const SEXP Allowed,           // in: constraints function
    const int *pnAllowedFuncArgs, // in: number of arguments to Allowed function, 3 or 4
    const SEXP Env,               // in: environment for Allowed function
    const int *pnUseBetaCache,    // in: 1 to use the beta cache, for speed
    const double *pTrace,         // in: 0 none 1 overview 2 forward 3 pruning 4 more pruning
    const char *sPredNames[]);    // in: predictor names in trace printfs, can be R_NilValue

void EvalSubsetsUsingXtxR(     // for use by R
    double       PruneTerms[], // out: specifies which cols in bx are in best set
    double       RssVec[],     // out: nTerms x 1
    const int    *pnCases,     // in
    const int    *pnResp,      // in: number of cols in y
    const int    *pnMaxTerms,  // in
    const double bx[],         // in: MARS basis matrix, all cols must be independent
    const double y[],          // in: nCases * nResp
    const double Weights[]);   // in: nCases x 1, can be R_NilValue

void RegressR(          // for testing earth routine Regress from R
    double       Betas[],       // out: nUsedCols * nResp
    double       Residuals[],   // out: nCases * nResp
    double       Rss[],         // out: RSS, summed over all nResp
    double       Diags[],       // out: diags of inv(transpose(bx) * bx)
    int          *pnRank,       // out: nbr of indep cols in x
    int          iPivots[],     // out: nCols, can be NULL
    const double x[],           // in: nCases x nCols
    const double y[],           // in: nCases x nResp
    const double Weightss[],    // in: nCases x 1, sqrt of Weights
    const int    *pnCases,      // in: number of rows in x and in y
    const int    *pnResp,       // in: number of cols in y
    int          *pnCols,       // in: number of columns in x, some may not be used
    const bool   UsedCols[]);   // in: specifies used columns in x

#endif // USING_R

#if STANDALONE
//#define bool char

void Earth(
    double *pBestGcv,       // out: GCV of the best model i.e. BestSet columns of bx
    int    *pnTerms,        // out: max term nbr in final model, after removing lin dep terms
    bool   BestSet[],       // out: nMaxTerms x 1, indices of best set of cols of bx
    double bx[],            // out: nCases x nMaxTerms
    int    Dirs[],          // out: nMaxTerms x nPreds, 1,0,-1 for term iTerm, predictor iPred
    double Cuts[],          // out: nMaxTerms x nPreds, cut for term iTerm, predictor iPred
    double Residuals[],     // out: nCases x nResp
    double Betas[],         // out: nMaxTerms x nResp
    const double x[],       // in: nCases x nPreds
    const double y[],       // in: nCases x nResp
    const double WeightsArg[], // in: nCases, can be NULL
    const int nCases,       // in: number of rows in x and elements in y
    const int nResp,        // in: number of cols in y
    const int nPreds,       // in: number of cols in x
    const int nMaxDegree,   // in: Friedman's mi
    const int nMaxTerms,    // in: includes the intercept term
    const double Penalty,   // in: GCV penalty per knot
    double Thresh,          // in: forward step threshold
    const int nMinSpan,     // in: set to non zero to override internal calculation
    const bool Prune,       // in: do backward pass
    const int nFastK,       // in: Fast MARS K
    const double FastBeta,  // in: Fast MARS ageing coef
    const double NewVarPenalty, // in: penalty for adding a new variable
    const int LinPreds[],       // in: 1 x nPreds, 1 if predictor must enter linearly
    const bool UseBetaCache,    // in: 1 to use the beta cache, for speed
    const double Trace,         // in: 0 none 1 overview 2 forward 3 pruning 4 more pruning
    const char *sPredNames[]);  // in: predictor names in trace printfs, can be NULL

void FormatEarth(
    const bool   UsedCols[],// in: nMaxTerms x 1, indices of best set of cols of bx
    const int    Dirs[],    // in: nMaxTerms x nPreds, 1,0,-1 for term iTerm, predictor iPred
    const double Cuts[],    // in: nMaxTerms x nPreds, cut for term iTerm, predictor iPred
    const double Betas[],   // in: nMaxTerms x nResp
    const int    nPreds,
    const int    nResp,     // in: number of cols in y
    const int    nTerms,
    const int    nMaxTerms,
    const int    nDigits,   // number of significant digits to print
    const double MinBeta);  // terms with abs(beta) less than this are not printed, 0 for all

void PredictEarth(
    double       y[],           // out: vector nResp
    const double x[],           // in: vector nPreds x 1 of input values
    const bool   UsedCols[],    // in: nMaxTerms x 1, indices of best set of cols of bx
    const int    Dirs[],        // in: nMaxTerms x nPreds, 1,0,-1 for iTerm iPred
    const double Cuts[],        // in: nMaxTerms x nPreds, cut for term iTerm predictor iPred
    const double Betas[],       // in: nMaxTerms x nResp
    const int    nPreds,        // in: number of cols in x
    const int    nResp,         // in: number of cols in y
    const int    nTerms,
    const int    nMaxTerms);

#endif // STANDALONE

/*
 * ORANGE INTERFACE
 */

#include "classify.hpp"
#include "learn.hpp"
#include "orange.hpp"
#include "domain.hpp"
#include "examplegen.hpp"
#include "table.hpp"
#include "examples.hpp"

class ORANGE_API TEarthLearner : public TLearner {
public:
	__REGISTER_CLASS

	TEarthLearner();

	int max_terms; //P Maximum number of terms.
	int max_degree; //P Maximum degree of terms.

	float penalty; //P Penalty.
	float threshold; //P Forward step threshold.
	bool prune; //P Prune terms (do backward pass).
	float fast_beta; //P Fast beta.
	float trace; //P Execution trace (for debugging only).
	int min_span; //P Min span.
	int fast_k;	//P Fast K.
	bool new_var_penalty; //P Penalty for adding a new variable.
	bool use_beta_cache; //P Use caching for betas.

	PClassifier operator()(PExampleGenerator, const int & = 0);

};

class ORANGE_API TEarthClassifier: public TClassifierFD {
public:
	__REGISTER_CLASS
	TEarthClassifier() {};
	TEarthClassifier(PDomain domain, bool * best_set, int * dirs, double * cuts, double *betas, int num_preds, int num_responses, int num_terms, int max_terms);
	TEarthClassifier(const TEarthClassifier & other);
	virtual ~TEarthClassifier();

	TValue operator()(const TExample&);
	std::string format_earth();

	int num_preds; //P
	int num_terms; //P
	int max_terms; //P
	int num_responses; //P

private:

	double* to_xvector(const TExample&);

	bool* best_set;
	int * dirs;
	double * cuts;
	double * betas;
};

WRAPPER(EarthLearner)
WRAPPER(EarthClassifier)

#endif // __EARTH_HPP