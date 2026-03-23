#include "pch.h"
#include "CppUnitTest.h"


extern "C" {
#include"../TP4_S2_TU/TP4_TU.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TP4S2TUtest
{
	TEST_CLASS(TP4S2TUtest)
	{
	public:

		TEST_METHOD(TestEstPair)
		{
			Assert::AreEqual(estPair(4), 1);
		}
		TEST_METHOD(TestEstPair2)
		{
			Assert::AreEqual(estPair(0), 1);
		}
		TEST_METHOD(TestEstPair3)
		{
			Assert::AreEqual(estPair(-2), 1);
		}
		TEST_METHOD(TestEstPair4)
		{
			Assert::AreEqual(estPair(-3), 0);
		}

		/* au début les tests ne passaient pas car la fonction estPair avait comme resultat du modulo 2 1 au lieu de 0*/



		TEST_METHOD(TestMax1)
		{
			Assert::AreEqual(max2(5, 3), 5);
		}
		TEST_METHOD(TestMax2)
		{
			Assert::AreEqual(max2(3, 5), 5);
		}
		TEST_METHOD(TestMax3)
		{
			Assert::AreEqual(max2(-1, -8), -1);
		}
		TEST_METHOD(TestMax4)
		{
			Assert::AreEqual(max2(4, 4), 4);
		}
		/* le test de max2(3,5) retourne 5 revele le bug car il retourne 3 et pas 5
		il fallait donc rajouter un else pour que quand b>a il retourne b et pas a */


		TEST_METHOD(TestFactorielle1) {
			Assert::AreEqual(factorielle(0), 1);
		}
		TEST_METHOD(TestFactorielle2) {
			Assert::AreEqual(factorielle(1), 1);
		}
		TEST_METHOD(TestFactorielle3) {
			Assert::AreEqual(factorielle(4), 24);
		}
		TEST_METHOD(TestFactorielle4) {
			Assert::AreEqual(factorielle(5), 120);
		}
		TEST_METHOD(TestFactorielle5) {
			Assert::AreEqual(factorielle(-3), 0);
		}
		/* le comportement sur les negatifs ne doit pas etre accépté et doit retourner 0 pour dire qu'il y a une erreur*/


		TEST_METHOD(TestMajuscule1) {
			Assert::AreEqual(contientMajuscule("bonjour"), 0);
		}
		TEST_METHOD(TestMajuscule2) {
			Assert::AreEqual(contientMajuscule("BonJour"), 1);
		}
		TEST_METHOD(TestMajuscule3) {
			Assert::AreEqual(contientMajuscule("ABC"), 1);
		}
		TEST_METHOD(TestMajuscule4) {
			Assert::AreEqual(contientMajuscule(""), 0);
		}
		TEST_METHOD(TestMajuscule5) {
			Assert::AreEqual(contientMajuscule(NULL), 0);
		}




		TEST_METHOD(TestDivisionExacte1) {
			Assert::AreEqual(divisionExacte(10, 2), 1);
		}
		TEST_METHOD(TestDivisionExacte2) {
			Assert::AreEqual(divisionExacte(10, 3), 0);
		}
		TEST_METHOD(TestDivisionExacte3) {
			Assert::AreEqual(divisionExacte(0, 5), 1);
		}
		/*ce cas est dangereux car on ne sait pas ce que fait une divison par 0*/
		TEST_METHOD(TestDivisionExacte4) {
			Assert::AreEqual(divisionExacte(10, 0), 0);
		}
		TEST_METHOD(TestSomme1)
		{
			const int tab[] = { 1, 2, 3 };
			Assert::AreEqual(sommeTableau(tab, 3), 6);
		}
		TEST_METHOD(TestSomme2) {
			const int tab[] = { 5 };
			Assert::AreEqual(sommeTableau(tab, 1), 5);
		}
		TEST_METHOD(TestSomme3) {
			const int tab[] = { -1, 4, -3 };
			Assert::AreEqual(sommeTableau(tab, 3), 0);
		}
		TEST_METHOD(TestSomme4) {
			Assert::AreEqual(sommeTableau(NULL, 0), 0);
		}

		TEST_METHOD(TestSomme6) {
			Assert::AreEqual(sommeTableau(NULL, 3), 0);
		}
		};
	}