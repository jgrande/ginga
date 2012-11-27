SET( ${PROJECT_NAME}_HEADER_FILES
	include/Parameter.h
	include/reuse/ReferNode.h
	include/reuse/ReferredNode.h
	include/Entity.h
	include/navigation/KeyNavigation.h
	include/navigation/FocusDecoration.h
	include/util/Comparator.h
	src/util/functions.h
	include/connectors/AttributeAssessment.h
	include/connectors/Action.h
	include/connectors/CompoundCondition.h
	include/connectors/CompoundStatement.h
	include/connectors/ValueAssessment.h
	include/connectors/SimpleCondition.h
	include/connectors/TriggerExpression.h
	include/connectors/CausalConnector.h
	include/connectors/Statement.h
	include/connectors/AssessmentStatement.h
	include/connectors/ConditionExpression.h
	include/connectors/ConnectorBase.h
	include/connectors/Connector.h
	include/connectors/CompoundAction.h
	include/connectors/SimpleAction.h
	include/connectors/Assessment.h
	include/connectors/Role.h
	include/connectors/EventUtil.h
	include/connectors/EventTransitionAssessment.h
	include/layout/LayoutRegion.h
	include/layout/RegionBase.h
	include/layout/types.h
	include/interfaces/TextAnchor.h
	include/interfaces/SampleIntervalAnchor.h
	include/interfaces/SwitchPort.h
	include/interfaces/PropertyAnchor.h
	include/interfaces/InterfacePoint.h
	include/interfaces/Anchor.h
	include/interfaces/CircleSpatialAnchor.h
	include/interfaces/SpatialAnchor.h
	include/interfaces/RectangleSpatialAnchor.h
	include/interfaces/Port.h
	include/interfaces/LabeledAnchor.h
	include/interfaces/ContentAnchor.h
	include/interfaces/LambdaAnchor.h
	include/interfaces/IntervalAnchor.h
	include/interfaces/RelativeTimeIntervalAnchor.h
	include/switches/CompositeRule.h
	include/switches/SwitchContent.h
	include/switches/Rule.h
	include/switches/RuleBase.h
	include/switches/SimpleRule.h
	include/switches/SwitchNode.h
	include/switches/DescriptorSwitch.h
	include/time/flexibility/LinearTimeCostFunction.h
	include/time/flexibility/TemporalFlexibilityFunction.h
	include/components/IllegalNodeTypeException.h
	include/components/NodeEntity.h
	include/components/ContextNode.h
	include/components/PrivateBase.h
	include/components/Node.h
	include/components/Content.h
	include/components/ContentNode.h
	include/components/CompositeNode.h
	include/Base.h
	include/animation/Animation.h
	include/metainformation/Meta.h
	include/metainformation/Metadata.h
	include/IPrivateBaseContext.h
	include/transition/TransitionUtil.h
	include/transition/TransitionBase.h
	include/transition/Transition.h
	include/NclDocument.h
	include/link/LinkComposition.h
	include/link/CausalLink.h
	include/link/Link.h
	include/link/Bind.h
	include/descriptor/GenericDescriptor.h
	include/descriptor/Descriptor.h
	include/descriptor/DescriptorBase.h
)

SET( ${PROJECT_NAME}_SOURCE_FILES
	${${PROJECT_NAME}_HEADER_FILES}
	src/reuse/ReferredNode.cpp
	src/reuse/ReferNode.cpp
	src/navigation/KeyNavigation.cpp
	src/navigation/FocusDecoration.cpp
	src/Base.cpp
	src/util/Comparator.cpp
	src/util/functions.cpp
	src/Parameter.cpp
	src/connectors/CompoundAction.cpp
	src/connectors/CompoundStatement.cpp
	src/connectors/CompoundCondition.cpp
	src/connectors/EventTransitionAssessment.cpp
	src/connectors/CausalConnector.cpp
	src/connectors/AssessmentStatement.cpp
	src/connectors/SimpleAction.cpp
	src/connectors/EventUtil.cpp
	src/connectors/SimpleCondition.cpp
	src/connectors/ValueAssessment.cpp
	src/connectors/Role.cpp
	src/connectors/Action.cpp
	src/connectors/ConnectorBase.cpp
	src/connectors/Connector.cpp
	src/connectors/AttributeAssessment.cpp
	src/connectors/TriggerExpression.cpp
	src/layout/RegionBase.cpp
	src/layout/LayoutRegion.cpp
	src/NclDocument.cpp
	src/interfaces/Port.cpp
	src/interfaces/LambdaAnchor.cpp
	src/interfaces/RelativeTimeIntervalAnchor.cpp
	src/interfaces/SwitchPort.cpp
	src/interfaces/RectangleSpatialAnchor.cpp
	src/interfaces/Anchor.cpp
	src/interfaces/TextAnchor.cpp
	src/interfaces/IntervalAnchor.cpp
	src/interfaces/LabeledAnchor.cpp
	src/interfaces/PropertyAnchor.cpp
	src/interfaces/SampleIntervalAnchor.cpp
	src/interfaces/CircleSpatialAnchor.cpp
	src/interfaces/ContentAnchor.cpp
	src/switches/SwitchContent.cpp
	src/switches/SwitchNode.cpp
	src/switches/Rule.cpp
	src/switches/DescriptorSwitch.cpp
	src/switches/RuleBase.cpp
	src/switches/CompositeRule.cpp
	src/switches/SimpleRule.cpp
	src/time/flexibility/TemporalFlexibilityFunction.cpp
	src/time/flexibility/LinearTimeCostFunction.cpp
	src/components/ContentNode.cpp
	src/components/Node.cpp
	src/components/CompositeNode.cpp
	src/components/PrivateBase.cpp
	src/components/NodeEntity.cpp
	src/components/Content.cpp
	src/components/ContextNode.cpp
	src/animation/Animation.cpp
	src/metainformation/Metadata.cpp
	src/metainformation/Meta.cpp
	src/Entity.cpp
	src/transition/Transition.cpp
	src/transition/TransitionUtil.cpp
	src/transition/TransitionBase.cpp
	src/link/CausalLink.cpp
	src/link/Link.cpp
	src/link/Bind.cpp
	src/descriptor/Descriptor.cpp
	src/descriptor/DescriptorBase.cpp
)
