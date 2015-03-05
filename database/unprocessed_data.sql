-- phpMyAdmin SQL Dump
-- version 3.3.2deb1ubuntu1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 05, 2015 at 03:21 PM
-- Server version: 5.1.73
-- PHP Version: 5.3.2-1ubuntu4.28

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
-- Table structure for table `test_unprocessed_data`
--

CREATE TABLE IF NOT EXISTS `test_unprocessed_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `device_id` char(4) NOT NULL,
  `timestamp` datetime NOT NULL,
  `data` blob NOT NULL,
  `unpacked` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `device_id` (`device_id`),
  KEY `timestamp` (`timestamp`),
  KEY `unpacked` (`unpacked`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=40020 ;

-- --------------------------------------------------------

--
-- Table structure for table `unprocessed_data`
--

CREATE TABLE IF NOT EXISTS `unprocessed_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `device_id` char(4) NOT NULL,
  `timestamp` datetime NOT NULL,
  `data` blob NOT NULL,
  `unpacked` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `device_id` (`device_id`),
  KEY `timestamp` (`timestamp`),
  KEY `unpacked` (`unpacked`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=28083 ;
