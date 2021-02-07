package link

import (
	"github.com/Dikower/LinkTamer/backend/database"
	"github.com/gofiber/fiber/v2"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
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

func New(c *fiber.Ctx) error {
	db := database.DBConn
	link := Link{Shorten: "", Url: ""}
	db.Create(&link)
	return c.JSON(link)
}
