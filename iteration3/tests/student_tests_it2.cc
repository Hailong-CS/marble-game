/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <string.h>
#include "../src/sensor_touch.h"
#include "../src/sensor_proximity.h"
#include "../src/sensor_distress.h"
#include "../src/sensor_entity_type.h"

#ifdef STUDENT_TEST_IT2_

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorTouch, Constructor) {
   csci3081::SensorTouch st;

   EXPECT_EQ(st.point_of_contact().x, 0) << "FAIL: Constructor!";
   EXPECT_EQ(st.point_of_contact().y, 0) << "FAIL: Constructor!";
   EXPECT_EQ(st.angle_of_contact(), 0) << "FAIL: Constructor!";
   EXPECT_EQ(st.activated(), false) << "FAIL: Constructor!";
}

TEST(SensorTouch, getter) {
   csci3081::SensorTouch st;

   EXPECT_EQ(st.point_of_contact().x, 0) << "FAIL: getter!";
   EXPECT_EQ(st.point_of_contact().y, 0) << "FAIL: getter!";
   EXPECT_EQ(st.angle_of_contact(), 0) << "FAIL: getter!";
   EXPECT_EQ(st.activated(), false) << "FAIL: getter!";
}

TEST(SensorTouch, setter) {
   csci3081::SensorTouch st;

   csci3081::Position p(10, 10);
   st.point_of_contact(p);
   st.angle_of_contact(10);
   st.activated(true);

   EXPECT_EQ(st.point_of_contact().x, 10) << "FAIL: setter!";
   EXPECT_EQ(st.point_of_contact().y, 10) << "FAIL: setter!";
   EXPECT_EQ(st.angle_of_contact(), 10) << "FAIL: setter!";
   EXPECT_EQ(st.activated(), true) << "FAIL: setter!";
}

TEST(SensorTouch, Accept) {
   csci3081::SensorTouch st;
   csci3081::EventCollision e;
   csci3081::Position p(10, 10);
   e.collided(1);
   e.point_of_contact(p);
   e.angle_of_contact(10);

   st.Accept(&e);

   EXPECT_EQ(st.activated(), true) << "FAIL: Accept!";
   EXPECT_EQ(st.point_of_contact().x, 10) << "FAIL: Accept!";
   EXPECT_EQ(st.point_of_contact().y, 10) << "FAIL: Accept!";
   EXPECT_EQ(st.angle_of_contact(), 10) << "FAIL: Accept!";

}

TEST(SensorTouch, Reset) {
   csci3081::SensorTouch st;

   st.Reset();

   EXPECT_EQ(st.activated(), false) << "FAIL: Reset!";
}

TEST(SensorProximity, Constructor) {
   csci3081::SensorProximity sp;

   EXPECT_DOUBLE_EQ(sp.get_length(), 0.0) << "FAIL: Bad length!";
   EXPECT_DOUBLE_EQ(sp.get_range(), 0.0) << "FAIL: Bad range!";
}

TEST(SensorProximity, Setters_and_getters) {
   csci3081::SensorProximity sp;
   
   sp.set_length(5.0);
   sp.set_range(2.0);
   EXPECT_DOUBLE_EQ(sp.get_length(), 5.0) << "FAIL: Bad set_length!";
   EXPECT_DOUBLE_EQ(sp.get_range(), 2.0) << "FAIL: Bad set_range!";
}

TEST(SensorProximity, Accept) {
   csci3081::SensorProximity sp;
   csci3081::EventCollision e;
   e.collided(1);
   sp.Accept(&e);

   EXPECT_EQ(sp.activated(), true) << "FAIL: Sense collision wrong!";
}

TEST(SensorProximity, change_direction) {
   csci3081::SensorProximity sp;

   EXPECT_DOUBLE_EQ(sp.change_direction(), 0.0) << "FAIL: can't change direction!";
}

TEST(SensorProximity, Reset) {
   csci3081::SensorProximity sp;
   sp.Reset();

   EXPECT_EQ(sp.activated(), false) << "FAIL: Reset function!";
}

TEST(SensorDistress, Constructor) {
	csci3081::SensorDistress sd;

	EXPECT_DOUBLE_EQ(sd.get_count(), 0.0) << "FAIL: Constructor!";
	EXPECT_DOUBLE_EQ(sd.get_range(), 0.0) << "FAIL: Constructor!";
}

TEST(SensorDistress, getter) {
	csci3081::SensorDistress sd;

	EXPECT_DOUBLE_EQ(sd.get_count(), 0.0) << "FAIL: getter!";
	EXPECT_DOUBLE_EQ(sd.get_range(), 0.0) << "FAIL: getter!";

}

TEST(SensorDistress, setter) {
	csci3081::SensorDistress sd;
	sd.set_count(5);
	sd.set_range(10);

	EXPECT_DOUBLE_EQ(sd.get_count(), 5.0) << "FAIL: setter!";
	EXPECT_DOUBLE_EQ(sd.get_range(), 10.0) << "FAIL: setter!";
}

TEST(SensorDistress, Accept) {
	csci3081::SensorDistress sd;
   csci3081::EventCollision e;
   e.collided(1);
   sd.Accept(&e);

   EXPECT_EQ(sd.activated(), true) << "FAIL: Accept!";
}

TEST(SensorDistress, Reset) {
	csci3081::SensorDistress sd;
	sd.Reset();

	EXPECT_EQ(sd.activated(), false) << "FAIL: Reset function!";
}

TEST(SensorEntityType, Constructor) {
   csci3081::SensorEntityType set;

   EXPECT_EQ(set.get_activated(), false) << "FAIL: Constructor!";
   EXPECT_EQ(set.get_type(), "" ) << "FAIL: Constructor!";
}

TEST(SensorEntityType, getters) {
   csci3081::SensorEntityType set;

   EXPECT_EQ(set.get_activated(), false) << "FAIL: getters!";
   EXPECT_EQ(set.get_type(), "" ) << "FAIL: getters!";
}

TEST(SensorEntityType, setters) {
   csci3081::SensorEntityType set;
   std::string type = "robot";
   set.set_type(type);
   set.set_activated(true);

   EXPECT_EQ(set.get_type(), "robot") << "FAIL: setters!";
   EXPECT_EQ(set.get_activated(), true) << "FAIL: setters!";
}

TEST(SensorEntityType, Accept) {
   csci3081::SensorEntityType set;
   csci3081::EventCollision e;
   e.collided(1);
   set.Accept(&e);

   EXPECT_EQ(set.get_activated(), true) << "FAIL: Accept!";
}

TEST(SensorEntityType, Reset) {
   csci3081::SensorEntityType set;
   set.Reset();

   EXPECT_EQ(set.get_activated(), false) << "FAIL: Reset!";
} 

#endif /* STUDENT_TEST_IT2_ */