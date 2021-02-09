package link

import (
	"github.com/Dikower/LinkTamer/backend/database"
	"github.com/gofiber/fiber/v2"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
	"math/rand"
)

type Link struct {
	gorm.Model
	Shorten string `json:"shorten"`
	Url     string `json:"url"`
}

func GetAll(c *fiber.Ctx) error {
	db := database.DBConn
	var links []Link
	db.Find(&links)
	return c.JSON(links)
}

const symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890"

func randStr(n int) string {
	res := make([]byte, n)
	for i := range res {
		res[i] = symbols[rand.Intn(len(symbols))]
	}
	return string(res)
}

func New(c *fiber.Ctx) error {
	type BodyLink struct {
		Url string `json:"url"`
	}
	var bodyLink BodyLink
	err := c.BodyParser(&bodyLink)
	if err != nil {
		return c.Status(fiber.StatusBadRequest).JSON(fiber.Map{
			"success": false,
			"message": "Can't parse json",
		})
	}
	db := database.DBConn
	newLink := Link{Shorten: randStr(5), Url: bodyLink.Url}
	db.Create(&newLink)
	return c.JSON(newLink)
}

func Get(c *fiber.Ctx) error {
	db := database.DBConn
	var link Link
	db.Where("shorten = ?", c.Params("shorten")).Find(&link)
	return c.JSON(link)
}
