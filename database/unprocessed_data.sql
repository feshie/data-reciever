-- phpMyAdmin SQL Dump
-- version 3.3.2deb1ubuntu1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Aug 10, 2014 at 10:09 AM
-- Server version: 5.1.73
-- PHP Version: 5.3.2-1ubuntu4.26

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `feshie`
--

-- --------------------------------------------------------

--
-- Table structure for table `unprocessed_data`
--

CREATE TABLE IF NOT EXISTS `unprocessed_data` (
  `ID` char(4) NOT NULL,
  `timestamp` datetime NOT NULL,
  `data` blob NOT NULL,
  PRIMARY KEY (`ID`,`timestamp`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
