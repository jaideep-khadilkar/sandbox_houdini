
#include "SOP_TemplateB.h"

#include <SOP/SOP_Guide.h>
#include <GU/GU_Detail.h>
#include <GA/GA_Iterator.h>
#include <OP/OP_AutoLockInputs.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_Matrix3.h>
#include <UT/UT_Matrix4.h>
#include <UT/UT_Vector3.h>
#include <SYS/SYS_Math.h>
#include <stddef.h>

#include <GU/GU_PrimPoly.h>
#include <GU/GU_PrimTube.h>
#include <GU/GU_PrimMetaBall.h>
#include <GU/GU_PrimNURBCurve.h>

void
newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        "templateB",
        "TemplateB",
        SOP_TemplateB::myConstructor,
		SOP_TemplateB::myTemplateList,
        1,
        1,
        NULL));
}

PRM_Template
SOP_TemplateB::myTemplateList[] = {
    PRM_Template(),
};

OP_Node *
SOP_TemplateB::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
    return new SOP_TemplateB(net, name, op);
}

SOP_TemplateB::SOP_TemplateB(OP_Network *net, const char *name, OP_Operator *op)
    : SOP_Node(net, name, op)
{
//    mySopFlags.setManagesDataIDs(true);

    mySopFlags.setNeedGuide1(false);
}

SOP_TemplateB::~SOP_TemplateB() {}

void SOP_TemplateB::ListAttribs(const GA_AttributeOwner& owner) {
	GA_AttributeDict attrib_dict = gdp->getAttributeDict(owner);
	for (auto it = attrib_dict.begin(GA_SCOPE_PUBLIC);
			it != attrib_dict.end(GA_SCOPE_PUBLIC);
			++it)
	{
		std::cout << "----------" << std::endl;
		std::cout << "Attribute Name : " << it.name() << std::endl;
		auto attrib = it.attrib();
		std::cout << "Attribute type : " << attrib->getType().getTypeName()
				<< std::endl;
		std::cout << "----------" << std::endl;
//		gdp->destroyAttribute(owner,it.name());
	}
}

void SOP_TemplateB::createFloatTupleAndFillData() {
	GA_Attribute* attrib = gdp->addFloatTuple(GA_ATTRIB_POINT,
			"cusotm_attrib_a", 5);
	GA_RWHandleF handle(attrib);
	int count = 0;
	for (GA_Iterator it(gdp->getPointRange()); !it.atEnd(); ++it) {
		GA_Offset offset = *it;
		for (int i = 0; i < 5; i++) {
			handle.set(offset, i, count);
			count++;
		}
	}
}

void SOP_TemplateB::findAttribAndReadData() {
	GA_ROHandleF handle = GA_ROHandleF(
			gdp->findAttribute(GA_AttributeOwner::GA_ATTRIB_VERTEX,
					"vtx_attribA"));
	GA_Offset ptoff;
	std::cout << "vtx_attribA : ";
	GA_FOR_ALL_PTOFF(gdp, ptoff)
		GA_FOR_ALL_PTOFF(gdp, ptoff) {
		std::cout << handle.get(ptoff) << "\t";
	}
	std::cout << std::endl;
}

void SOP_TemplateB::createStringTupleAndFillData() {
	GA_Attribute* attrib = gdp->addStringTuple(GA_ATTRIB_POINT,
			"cusotm_attrib_b", 2);
	GA_RWHandleS handle(attrib);
	for (GA_Iterator it(gdp->getPointRange()); !it.atEnd(); ++it) {
		GA_Offset offset = *it;
		for (int i = 0; i < 2; i++) {
			handle.set(offset, i, "test");
		}
	}
}

void SOP_TemplateB::createGroupAndSetData() {
	GA_ElementGroup* group = gdp->createElementGroup(GA_ATTRIB_POINT,
			"custom_group_a");
	int count = 0;
	for (GA_Iterator it(gdp->getPointRange()); !it.atEnd(); ++it) {
		GA_Offset offset = *it;
		if (count % 3 == 0) {
			group->setOffset(offset, true);
		}
		count++;
	}
}

OP_ERROR
SOP_TemplateB::cookMySop(OP_Context &context)
{
    // We must lock our inputs before we try to access their geometry.
    // OP_AutoLockInputs will automatically unlock our inputs when we return.
    // NOTE: Don't call unlockInputs yourself when using this!
    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();

    duplicateSource(0, context);

	std::cout << "=============GA_ATTRIB_VERTEX=============" << std::endl;
	ListAttribs(GA_AttributeOwner::GA_ATTRIB_VERTEX);
	std::cout << "=============GA_ATTRIB_POINT=============" << std::endl;
	ListAttribs(GA_AttributeOwner::GA_ATTRIB_POINT);
	std::cout << "=============GA_ATTRIB_PRIMITIVE=============" << std::endl;
	ListAttribs(GA_AttributeOwner::GA_ATTRIB_PRIMITIVE);
	std::cout << "=============GA_ATTRIB_DETAIL=============" << std::endl;
	ListAttribs(GA_AttributeOwner::GA_ATTRIB_DETAIL);

	findAttribAndReadData();
	createFloatTupleAndFillData();
	createStringTupleAndFillData();
	createGroupAndSetData();

    return error();
}

const char *
SOP_TemplateB::inputLabel(unsigned) const
{
    return "Geometry to Analyze";
}
