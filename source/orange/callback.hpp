/*
    This file is part of Orange.

    Orange is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Orange is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Orange; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Authors: Janez Demsar, Blaz Zupan, 1996--2002
    Contact: janez.demsar@fri.uni-lj.si
*/


#ifndef __CALLBACK_HPP
#define __CALLBACK_HPP

#include "Python.h"


PyObject *setCallbackFunction(PyObject *self, PyObject *func);

#include "filter.hpp"
class TFilter_Python : public TFilter {
public:
  __REGISTER_CLASS
  bool operator()(const TExample &ex);
};


#include "transval.hpp"
class TTransformValue_Python : public TTransformValue {
public:
  __REGISTER_CLASS
  void transform(TValue &);
};


#include "measures.hpp"
class TMeasureAttribute_Python : public TMeasureAttribute {
public:
  __REGISTER_CLASS
  TMeasureAttribute_Python();
  virtual float operator()(PContingency, PDistribution classDistribution, PDistribution apriorClass=PDistribution());
  virtual float operator()(int attrNo, PDomainContingency, PDistribution apriorClass=PDistribution());

private:
  float callMeasure(PyObject *args);
};


#include "learn.hpp"
class TLearner_Python : public TLearner {
public:
  __REGISTER_CLASS
  virtual PClassifier operator()(PExampleGenerator, const int &);
};


#include "logfit.hpp"
class TLogRegFitter_Python : public TLogRegFitter {
public:
  __REGISTER_CLASS
  virtual PAttributedFloatList operator()(PExampleGenerator, const int &, PAttributedFloatList &, float &, int &, PVariable &);
};


#include "classify.hpp"
class TClassifier_Python : public TClassifier {
public:
  __REGISTER_CLASS
  virtual TValue operator ()(const TExample &);
  virtual PDistribution classDistribution(const TExample &);
  virtual void predictionAndDistribution(const TExample &, TValue &, PDistribution &);
};


#include "tdidt.hpp"
#include "tdidt_split.hpp"
#include "tdidt_stop.hpp"

class TTreeSplitConstructor_Python : public TTreeSplitConstructor {
public:
  __REGISTER_CLASS
  virtual PClassifier operator ()(PStringList &, PDiscDistribution &, float &, int &, PExampleGenerator, const int & =0, PDomainContingency =PDomainContingency(), PDistribution = PDistribution(), const vector<bool> & = vector<bool>(), PClassifier nodeClassifier = PClassifier());
};


class TTreeStopCriteria_Python : public TTreeStopCriteria {
public:
  __REGISTER_CLASS
  virtual bool operator()(PExampleGenerator gen, const int & =0, PDomainContingency =PDomainContingency());
};


class TTreeDescender_Python : public TTreeDescender {
public:
  __REGISTER_CLASS
  virtual PTreeNode operator() (PTreeNode node, const TExample &, PDiscDistribution &);
};


class TTreeExampleSplitter_Python : public TTreeExampleSplitter {
public:
  __REGISTER_CLASS
  virtual PExampleGeneratorList operator() (PTreeNode node, PExampleGenerator generator, const int &weightID, vector<int> &weights);
};


#include "progress.hpp"

class TProgressCallback_Python : public TProgressCallback {
public:
  __REGISTER_CLASS
  virtual bool operator()(const float &, POrange);
};


#include "imputation.hpp"

class TImputerConstruct_Python : public TImputerConstructor {
public:
  __REGISTER_CLASS
  virtual PImputer operator()(PExampleGenerator, const int &);
};


class TImputer_Python : public TImputer {
public:
  __REGISTER_CLASS
  virtual TExample *operator()(TExample &example);
};

#include "rulelearner.hpp"

class TRuleEvaluator_Python : public TRuleEvaluator {
public:
  __REGISTER_CLASS
  virtual float operator()(PRule, PExampleTable, const int &, const int &targetClass, PDistribution) const;
};

class TRuleValidator_Python : public TRuleValidator {
public:
  __REGISTER_CLASS
  virtual bool operator()(PRule, PExampleTable, const int &, const int &targetClass, PDistribution) const;
};

class TRuleCovererAndRemover_Python : public TRuleCovererAndRemover {
public:
  __REGISTER_CLASS
  virtual PExampleTable operator()(PRule, PExampleTable, const int &weightID, int &newWeight, const int &targetClass = -1) const;
};

class TRuleStoppingCriteria_Python : public TRuleStoppingCriteria {
public:
  __REGISTER_CLASS
  virtual bool operator()(PRuleList, PRule, PExampleTable, const int &weightID) const;
};

class TRuleDataStoppingCriteria_Python : public TRuleDataStoppingCriteria {
public:
  __REGISTER_CLASS
  virtual bool operator()(PExampleTable, const int &weightID, const int &targetClass) const;
};

class TRuleFinder_Python : public TRuleFinder {
public:
  __REGISTER_CLASS
  virtual PRule operator()(PExampleTable, const int &weightID, const int &targetClass, PRuleList baseRules = PRuleList());
};

/*class TRuleBeamFilter_Python : public TRuleBeamFilter {
public:
  __REG ISTER_CLASS
  virtual void operator()(PRuleList existingRules, PExampleTable, const int &weightID);
};*/

class TRuleBeamRefiner_Python : public TRuleBeamRefiner {
public:
  __REGISTER_CLASS
  virtual PRuleList operator()(PRule rule, PExampleTable, const int &weightID, const int &targetClass = -1);
};

class TRuleBeamInitializer_Python : public TRuleBeamInitializer {
public:
  __REGISTER_CLASS
  virtual PRuleList operator()(PExampleTable, const int &weightID, const int &targetClass, PRuleList baseRules, PRuleEvaluator, PDistribution prior, PRule &bestRule);
};

class TRuleBeamCandidateSelector_Python : public TRuleBeamCandidateSelector {
public:
  __REGISTER_CLASS
  virtual PRuleList operator()(PRuleList existingRules, PExampleTable, const int &weightID);
};

class TRuleBeamFilter_Python : public TRuleBeamFilter {
public:
  __REGISTER_CLASS
  virtual void operator()(PRuleList rules, PExampleTable, const int &weightID);
};

class TRuleClassifierConstructor_Python : public TRuleClassifierConstructor {
public:
  __REGISTER_CLASS
  virtual PRuleClassifier operator ()(PRuleList, PExampleTable, const int &weightID);
};

/*
Not verified yet:

#include "decomposition.hpp"
class TConstructIM_Python : public TConstructIM {
public:
  __ R E G I S T E R _ C L A S S
  virtual PIM operator() (PExampleGenerator, const vector<bool> &bound, const TVarList &boundSet, const vector<bool> &free, const int &weightID=0);
};
*/

// This is defined by Python but then redefined by STLPort
#undef LONGLONG_MAX
#undef ULONGLONG_MAX
#endif
